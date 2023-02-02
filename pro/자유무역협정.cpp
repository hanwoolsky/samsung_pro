#include <string>
#include <cstring>
#include <unordered_map>

#define MAXN			(500)
#define MAXL			(11)
#define MAX_ENT (1000)
using namespace std;

int parent[MAX_ENT + 1];
int visit[MAX_ENT + 1];
int cnt[MAX_ENT + 1];
int collaboration[MAX_ENT + 1][MAX_ENT + 1];

int numA, total, vn;
unordered_map<string, int> reHash;

void init(int mNumA, char mCompanyListA[MAXN][MAXL], int mNumB, char mCompanyListB[MAXN][MAXL]) {
	numA = mNumA;
	total = mNumA + mNumB;
	reHash.clear();
	memset(visit, 0, sizeof(visit));
	memset(cnt, 1, sizeof(cnt));
	memset(collaboration, 0, sizeof(collaboration));
    
	int i = 0;
	for (i = 0; i < mNumA; i++) {
		reHash.insert({ mCompanyListA[i], i });
		parent[i] = i;
        cnt[i] = 1;
	}
	for (i = 0; i < mNumB; i++) {
		reHash.insert({ mCompanyListB[i], i + mNumA });
		parent[i + mNumA] = i + mNumA;
        cnt[i + mNumA] = 1;
	}

}

int find(int x) {
	if (x == parent[x]) return x;
	return parent[x] = find(parent[x]);
}

void startProject(char mCompanyA[MAXL], char mCompanyB[MAXL]){
	int rootA = find(reHash[mCompanyA]);
	int rootB = find(reHash[mCompanyB]);

	collaboration[rootA][rootB]++;
	collaboration[rootB][rootA]++;
}

void finishProject(char mCompanyA[MAXL], char mCompanyB[MAXL]){
	int rootA = find(reHash[mCompanyA]);
	int rootB = find(reHash[mCompanyB]);

	collaboration[rootA][rootB]--;
	collaboration[rootB][rootA]--;
}

void ally(char mCompany1[MAXL], char mCompany2[MAXL]) {
	int root1 = find(reHash[mCompany1]);
	int root2 = find(reHash[mCompany2]);

	if (root1 == root2) return;

	parent[root2] = root1;
	cnt[root1] += cnt[root2];
	cnt[root2] = 0;

	for (int i = 0; i < total; i++) { // root2가 root1에 흡수되었으니 project도 root1으로 옮기기
		collaboration[root1][i] += collaboration[root2][i];
		collaboration[i][root1] += collaboration[i][root2];
		collaboration[i][root2] = collaboration[root2][i] = 0;
	}
}

int conflict(char mCompany1[MAXL], char mCompany2[MAXL]) {
	int conf1 = find(reHash[mCompany1]);
	int conf2 = find(reHash[mCompany2]);

	int ans = 0;
	int tg = ++vn; // conflict가 한번 일어나고 모든 visit을 0으로 초기화할 수 없으므로 매 스텝마다 ++한 값과 비교
	for (int i = 0; i < total; i++) {
		if(collaboration[conf1][i]) visit[find(i)] = tg;
	}
	for (int i = 0; i < total; i++) {
		if (collaboration[conf2][i]) {
			int k = find(i);
			if (visit[k] == tg) {
				visit[k] = tg - 1;
				ans += cnt[k];
			}
		}
	}

	return ans;
}