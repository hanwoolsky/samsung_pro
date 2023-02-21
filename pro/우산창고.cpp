// 56ms
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
using pii = pair<int, int>;
const int LM = 10005;
int n, par[LM], dist[LM]; // n: 노드수, par[]: 부모노드, dist[]: 부모노드까지 거리
int quant[LM], total[LM]; // quant[]: 우산수, total[]: 자손노드에 있는 우산의 총합
vector<int> adj[LM]; // 인접배열
int visited[LM], vcnt; // 방문체크배열


void init(int N, int mParent[], int mDistance[], int mQuantity[]){
    for (int i = 0; i < n; ++i) adj[i].clear(); // 이전 데이터 초기화
    // *** 새로운 데이터 셋팅 *** //
    n = N;
    for (int i = 0; i < n; ++i) {
        par[i] = mParent[i], dist[i] = mDistance[i];
        total[i] = quant[i] = mQuantity[i];
        adj[i].push_back(par[i]);
        adj[par[i]].push_back(i);
    }
    for (int i = n - 1; i >= 0; --i) { // 자손노드 우산의 총합 구하기
        for (int j : adj[i]) {
            if (j > i) total[i] += total[j];
        }
    }
}


int carry(int mFrom, int mTo, int mQuantity){
    quant[mFrom] -= mQuantity, quant[mTo] += mQuantity; // 우산량 업데이트
    int distSum = 0;
    while(mFrom != mTo) {
        if (mFrom > mTo) {// 노드번호가 큰것부터 처리
            total[mFrom] -= mQuantity, distSum += dist[mFrom];
            mFrom = par[mFrom];
        }
        else {
            total[mTo] += mQuantity, distSum += dist[mTo];
            mTo = par[mTo];
        }
    }
    return mQuantity * distSum;
}


int gather(int mID, int mQuantity){
    quant[mID] += mQuantity;
    priority_queue<pii, vector<pii>, greater<pii>> pq; // <first:Dist-ASC, second:id-ASC>
    priority_queue<int> entry; // total[node] 업데이트가 필요한 노드 목록 < int:id-DESC >
    pq.push({ 0, mID });
    visited[mID] = ++vcnt;
    int retCost = 0;
    while (mQuantity) {
        int dst = pq.top().first; // mID 로부터 u 까지 거리
        int u = pq.top().second;
        pq.pop();
        entry.push(u);
        if (u != mID) { // mID가 아닌 경우만 처리
            int minCnt = min(mQuantity, quant[u]);
            mQuantity -= minCnt, quant[u] -= minCnt;
            retCost += minCnt * dst;
            if (mQuantity == 0) break;
        }
        for (auto v : adj[u]) {
            if (visited[v] < vcnt) {
                visited[v] = vcnt;
                if (v < u) pq.push({ dst + dist[u], v }); // v는 u의 부모노드이다. 따라서 거리는 u 에 있다.
                else pq.push({ dst + dist[v], v });
            }
        }
    }

    while (!entry.empty()) { // 자손노드 우산의 총합 다시 구하기
        int u = entry.top();
        entry.pop();
        total[u] = quant[u];
        for (int v : adj[u]) {
            if (v > u) total[u] += total[v];
        }
    }
    return retCost;
}

int sum(int mID){
    return total[mID];
}

// 좋았던 풀이
#include <algorithm>
#include <vector>
#include <queue>
#include <memory.h>
  
using namespace std;
  
const int MAX_N = 10000;  
int n;
int parent[MAX_N];
int dist[MAX_N];
int quantity[MAX_N];
vector<pair<int, int>> child[MAX_N]; 
int descendantSum[MAX_N];
  
void updateDescendantSum(int now){
    descendantSum[now] = quantity[now];
    for (auto c : child[now]){
        updateDescendantSum(c.first);
        descendantSum[now] += descendantSum[c.first];
    }
}
  
void init(int N, int mParent[], int mDistance[], int mQuantity[]){
    for (int i = 0; i < n; i++) child[i].clear();
    n = N;
    for (int i = 0; i < N; i++){
        parent[i] = mParent[i];
        dist[i] = mDistance[i];
        quantity[i] = mQuantity[i];
        if (parent[i] != -1) child[parent[i]].push_back({i, mDistance[i]});
    }
    updateDescendantSum(0);
}
  
  
vector<int> pathFromRoot(int mID){
    vector<int> path;
    path.push_back(mID);
    while (mID != 0){
        mID = parent[mID];
        path.push_back(mID);
    }
    reverse(path.begin(), path.end());
    return path;
}
  
int carry(int mFrom, int mTo, int mQuantity){
    vector<int> pathF = pathFromRoot(mFrom);
    vector<int> pathT = pathFromRoot(mTo);
  
    int allDistance = 0;
    for (int i = 0; i < pathF.size(); i++){
        if (i >= pathT.size() || pathF[i] != pathT[i]) allDistance += dist[pathF[i]];
    }
    for (int i = 0; i < pathT.size(); i++){
        if (i >= pathF.size() || pathF[i] != pathT[i]) allDistance += dist[pathT[i]];
    }
  
    quantity[mFrom] -= mQuantity;
    quantity[mTo] += mQuantity;
  
    for (auto now : pathF) descendantSum[now] -= mQuantity;
    for (auto now : pathT) descendantSum[now] += mQuantity;
  
    return allDistance * mQuantity;
}
  
bool isVisited[MAX_N];
priority_queue<pair<int, int>> pq;
  
int gather(int mID, int mQuantity){
    int cost = 0;
    quantity[mID] += mQuantity;
    pq = {};
    pq.push({0, -mID});
    memset(isVisited, false, sizeof(bool) * n);
    isVisited[mID] = true; 
  
    while (!pq.empty()){
        int now = -pq.top().second;
        int nowDist = -pq.top().first;
        if (now != mID){
            if (mQuantity <= quantity[now]){
                cost += mQuantity * nowDist;
                quantity[now] -= mQuantity;
                break;
            }
            else {
                cost += quantity[now] * nowDist;
                mQuantity -= quantity[now];
                quantity[now] = 0;
            }
        }
        pq.pop();
        if (parent[now] != -1 && !isVisited[parent[now]]){
            pq.push({-nowDist - dist[now], -parent[now]});
            isVisited[parent[now]] = true;
        }
        for (auto c : child[now]){
            if (!isVisited[c.first]){
                pq.push({-nowDist - c.second, -c.first});
                isVisited[c.first] = true;
            }
        }
    }
    updateDescendantSum(0);
    
    return cost;
}
  
  
int sum(int mID)
{
    return descendantSum[mID];
}

// My : memory limit exceed



// heap
#define MAX_N 10005
#define FOR(i,x,n) for(register int i = x ; i < n ; i++)
#define IFOR(i,x,n) for(register int i = x ; i >= n ; i--)
struct Storage {
    Storage* parent; // 부모
    int distance;
    int quantity;
    int subAllQuantity;
    int depth;
 
}storage[MAX_N];
 
struct LL {
    int id;
    int len;
    LL* next;
}pool[MAX_N * 2 + 1];
 
LL* malloc = pool;
LL * adj[MAX_N];
 
struct Dst {
    int distance;
    int cur;
}dpool[MAX_N];
 
 
#define comp(A,B) ((((dst[(A)]).distance) != ((dst[(B)]).distance)) ? (((dst[(A)]).distance) < ((dst[(B)]).distance)) : ((dst[(A)]).cur < (dst[(B)]).cur))
struct Heap {
    int H[MAX_N];
    int N;
    Dst* dst;
    void init(Dst * _dst) {
        dst = _dst;
        N = 0;
    }
    void push(int idx) {
        H[N] = idx;
        up(N++);
    }
    int pop() {
        int ret = H[0];
        H[0] = H[--N];
        down(0);
        return ret;
    }
    void up(int idx) {
        register int c, p, cmps;
        c = idx;
        p = idx >> 1;
        cmps = H[c];
        while (c > 0) {
            if (comp(cmps, H[p])) {
                H[c] = H[p];
            }
            else break;
            c = p;
            p >>= 1;
        }
        H[c] = cmps;
    }
    void down(int idx) {
        register int c, p, cmps;
        p = idx;
        c = !p ? 1 : p << 1;
        cmps = H[p];
        while (c < N) {
            if (c + 1 < N && comp(H[c + 1], H[c]))
                c++;
            if (comp(H[c], cmps)) {
                H[p] = H[c];
            }
            else break;
            p = c;
            c <<= 1;
        }
        H[p] = cmps;
    }
}H;
int N;
void init(int N, int mParent[], int mDistance[], int mQuantity[])
{
    malloc = pool;
     
    ::N = N;
    FOR(i, 0, N)
        adj[i] = 0;
    storage[0] = { 0,0,mQuantity[0],mQuantity[0],0 };
    FOR(i, 1, N) {
         
        int parent = mParent[i];
        int dist = mDistance[i];
        storage[i] = { &storage[parent],mDistance[i],mQuantity[i],mQuantity[i],storage[parent].depth + 1};
 
        // add adj
        LL* newLL = malloc++;
        *newLL = { parent,dist,adj[i] };
        adj[i] = newLL;
        newLL = malloc++;
        *newLL = {i,dist,adj[parent]};
        adj[parent] = newLL;
        // add adj
 
    }
    IFOR(i, N - 1, 1) {
        storage[i].parent->subAllQuantity += storage[i].subAllQuantity;
    }
}
 
int carry(int mFrom, int mTo, int mQuantity)
{
    int ret = 0;
    Storage* from = &storage[mFrom];
    Storage* to = &storage[mTo];
    from->quantity -= mQuantity;
    to->quantity += mQuantity;
    while (from->depth > to->depth) {
        from->subAllQuantity -= mQuantity;
        ret += from->distance;
        from = from->parent;
    }
    while (from->depth < to->depth) {
        to->subAllQuantity += mQuantity;
        ret += to->distance;
        to = to->parent;
    }
    while (from != to) {
        from->subAllQuantity -= mQuantity;
        ret += from->distance;
        from = from->parent;
        to->subAllQuantity += mQuantity;
        ret += to->distance;
        to = to->parent;
    }
    // from == to
    return ret * mQuantity;
}
 
int dist[10005];
 
#define INF 0x0FFFFFFF
int gather(int mID, int mQuantity)
{
    int ret = 0;
    int dCnt = 0;
    FOR(i, 0, N)
        dist[i] = INF;
    H.init(dpool);
    dist[mID] = 0; //제외
 
    int pop = mID;
    LL* cur = adj[mID];
    while (cur) { //push
        if (dist[cur->id] > dist[pop] + cur->len) {
            dist[cur->id] = dist[pop] + cur->len;
            dpool[dCnt] = { dist[cur->id] , cur->id };
            H.push(dCnt++);
        }
        cur = cur->next;
    }
 
    while (mQuantity && H.N) {
        int pop = dpool[H.pop()].cur;
        LL* cur = adj[pop];
        int move = 0;
        if (mQuantity >= storage[pop].quantity) {
            move = storage[pop].quantity;
        }
        else
            move = mQuantity;
        mQuantity -= move;
        if(move)
            ret += carry(pop, mID, move);
        while (cur) {
            if (dist[cur->id] > dist[pop] + cur->len) {
                dist[cur->id] = dist[pop] + cur->len;
                dpool[dCnt] = { dist[cur->id] , cur->id };
                H.push(dCnt++);
            }
            cur = cur->next;
        }
    }
    return ret;
}
 
int sum(int mID)
{
    return storage[mID].subAllQuantity;
}