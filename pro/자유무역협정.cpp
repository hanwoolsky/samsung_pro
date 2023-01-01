#include <unordered_map>
#include <string>
#include <cstring>
 
#define MAXN (500)
#define MAXL (11)
 
using namespace std;
unordered_map<string, int> hmap;
 
int numA, total;
int parent[1001], cnt[1001];
int partner[1001][1001];
int visited[1001], vn;
 
int findRoot(int x) {
    if (parent[x] == x) return x;
 
    return parent[x] = findRoot(parent[x]);
}
 
void init(int mNumA, char mCompanyListA[MAXN][MAXL], int mNumB, char mCompanyListB[MAXN][MAXL])
{
    numA = mNumA, total = mNumA + mNumB;
    hmap.clear();
 
    int i, j = 0;
    for (i = 0; i < mNumA; ++i) hmap[mCompanyListA[i]] = ++j;
    for (i = 0; i < mNumB; ++i) hmap[mCompanyListB[i]] = ++j;
    for (i = 1; i <= total; ++i) parent[i] = i, cnt[i] = 1;
    memset(partner, 0, sizeof(partner));
}
 
void startProject(char mCompanyA[MAXL], char mCompanyB[MAXL])
{
    int idxA = hmap[mCompanyA], idxB = hmap[mCompanyB];
    int rootA = findRoot(idxA), rootB = findRoot(idxB);
    partner[rootA][rootB]++, partner[rootB][rootA]++;
}
 
void finishProject(char mCompanyA[MAXL], char mCompanyB[MAXL])
{
    int idxA = hmap[mCompanyA], idxB = hmap[mCompanyB];
    int rootA = findRoot(idxA), rootB = findRoot(idxB);
    partner[rootA][rootB]--, partner[rootB][rootA]--;
}
 
void ally(char mCompany1[MAXL], char mCompany2[MAXL])
{
    int idxA = hmap[mCompany1], idxB = hmap[mCompany2];
    int rootA = findRoot(idxA), rootB = findRoot(idxB);
 
    if (rootA == rootB) return;
 
    parent[rootB] = rootA;
    cnt[rootA] += cnt[rootB], cnt[rootB] = 0;
 
    for (int i = 1; i <= total; ++i) {
        partner[rootA][i] += partner[rootB][i]; // rootA와 rootB가 둘 다 j 국가와 공동프로젝트를 진행하고 있다면 중복 아닌가?
        partner[i][rootA] += partner[rootB][i];
        partner[rootB][i] = partner[i][rootB] = 0;
    }
}
 
int conflict(char mCompany1[MAXL], char mCompany2[MAXL]){
    int idxA = hmap[mCompany1], idxB = hmap[mCompany2];
    int rootA = findRoot(idxA), rootB = findRoot(idxB);
     
    int ret = 0, tg = ++vn;
    for (int i = 1; i <= total; ++i) {
        if (partner[rootA][i]) {
            visited[findRoot(i)] = tg;
        }
    }
    for (int i = 1; i <= total; ++i) {
        if (partner[rootB][i]) {
            int k = findRoot(i);
            if (visited[k] == tg) {
                visited[k] = tg - 1;
                ret += cnt[k];
            }
        }
    }
 
    return ret;
}