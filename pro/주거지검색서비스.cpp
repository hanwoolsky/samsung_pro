#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define MAX_N (3000)

void init(int, int[]);
void newLine(int, int[], int[]);
void changeLimitDistance(int);
int findCity(int, int[]);


#define CMD_INIT (100)
#define CMD_ADD  (200)
#define CMD_FIND (300)

static int N;
static int M;
static int mDownTown[3];
static int city_id_list[MAX_N + 5];
static int distance_list[MAX_N + 5];
static int downtown_list[4];

static bool run()
{
    int query_num;
    scanf("%d", &query_num);

    int ret, ans;
    bool ok = false;

    for (int q = 0; q < query_num; q++)
    {
        int query;
        scanf("%d", &query);

        if (query == CMD_INIT)
        {
            scanf("%d", &N);
            for (int i = 0; i < 3; i++)
            {
                scanf("%d", &mDownTown[i]);
            }
            init(N, mDownTown);
            ok = true;
        }
        else if (query == CMD_ADD)
        {
            int mLimitDistance;

            scanf("%d%d", &M, &mLimitDistance);
            for (int i = 0; i < M; i++)
            {
                scanf("%d", city_id_list + i);
            }
            for (int i = 0; i < M - 1; i++)
            {
                scanf("%d", distance_list + i);
            }
            newLine(M, city_id_list, distance_list);
            changeLimitDistance(mLimitDistance);
        }
        else if (query == CMD_FIND)
        {
            int mOpt;
            scanf("%d", &mOpt);

            for (int i = 0; i < mOpt; i++)
            {
                scanf("%d", downtown_list + i);
            }
            ret = findCity(mOpt, downtown_list);
            scanf("%d", &ans);

            if (ans != ret)
            {
                ok = false;
            }
        }
    }
    return ok;
}

int main()
{
    setbuf(stdout, NULL);
    //    freopen("sample_input.txt", "r", stdin);
    int T, MARK;
    scanf("%d %d", &T, &MARK);

    for (int tc = 1; tc <= T; tc++)
    {
        int score = run() ? MARK : 0;
        printf("#%d %d\n", tc, score);
    }
    return 0;
}

#include <vector>
#include <set>
#include <queue>
using namespace std;
using UI = unsigned int;
using pii = pair<UI, int>; // <UI(가격 거리, id)>
const int LM = 3001;
const int INF = 1 << 20;
int n; // 도시 수
int limit; // 한계 거리
int hub[3]; // 중심도시
int visited[LM], vn; // 도시 방문 체크 : Dijkstra() 에서 사용
int price[LM]; // 주택가격
int dist[3][LM]; // 각 중심도시로부터의 거리
int D[LM][LM]; // 인접 배열에서 사용되는 두 도시간 거리
int types[LM];
vector<int> adj[LM]; // 인접 배열
set<pii> myset[8]; // <(price<<17)+dist, id>

void init(int N, int mDownTown[]) {
    for (int i = 1; i <= n; ++i) { // 이전 자료 초기화
        for (int j : adj[i]) D[i][j] = 0; // 인접행렬 초기화(사용된 것만)
        adj[i].clear(); // 인접배열 초기화
        price[i] = 0; // 주택 가격 초기화
    }
    n = N; // 현재 TC 도시수 초기화
    for (int i = 0; i < 3; ++i) {
        hub[i] = mDownTown[i]; // 중심도시 저장
        types[hub[i]] = i; // i번 중심도시의 번호
        price[hub[i]] = INF; // 중시도시 주택가격 최고로(최단거리 목록에서 제외할 목적)
    }
}
void newLine(int M, int mCityIDs[], int mDistances[]) {
    for (int i = 0; i < M - 1; ++i) { // 인접행렬 생성(업데이트)과 인접배열 생성하기
        int s = mCityIDs[i], e = mCityIDs[i + 1];
        if (!D[s][e]) { // 인접행렬 생성 & 인접배열 생성
            adj[s].push_back(e), adj[e].push_back(s);
            D[s][e] = D[e][s] = mDistances[i];
        }
        else D[s][e] = D[e][s] = min(D[s][e], mDistances[i]); // 인접행렬 업데이트
    }
}

void Dijkstra(int src, int* drr) { // O(ElogV) Dijkstra
    for (int i = 1; i <= n; ++i) drr[i] = INF;
    drr[src] = 0; // src를 시점으로 최단거리 구하기
    ++vn;
    priority_queue<pii, vector<pii>, greater<pii>> pq; // <int:drr, int:id>
    pq.push({ 0, src });
    while (!pq.empty()) {
        int u = pq.top().second, d = pq.top().first;
        pq.pop();
        if (visited[u] == vn) continue;
        visited[u] = vn;
        for (int v : adj[u]) if (visited[v] < vn) {
            int nd = d + D[u][v];
            if (nd < drr[v]) {
                drr[v] = nd;
                pq.push({ nd, v });
            }
        }
    }
}

void changeLimitDistance(int mLimitDistance) {
    limit = mLimitDistance;
    // 각 중심도시를 시점으로 모든 다른 도시까지 최단거리 구하기
    for (int i = 0; i < 3; ++i) {
        Dijkstra(hub[i], dist[i]);
    }
    for (int i = 1; i <= 7; ++i) // 유형별 set 초기화
        myset[i].clear();
    for (int i = 1; i <= n; ++i) { // 각 도시별로 set[type]에 <city_id, type> 저장
        if (price[i] == INF) continue;
        int a = dist[0][i], b = dist[1][i], c = dist[2][i];
        for (int j = 1; j <= 7; ++j) {
            int nd = (j & 1) * a + ((j >> 1) & 1) * b + ((j >> 2) & 1) * c;
            if (nd <= limit) // 제한거리를 만족하는 경우만 추가
                myset[j].insert({ ((UI)price[i] << 17) | nd, i });
        }
    }
}

int findCity(int mOpt, int mDestinations[]) {
    int k = 0;
    for (int i = 0; i < mOpt; ++i) { // 주어진 중심도시로 만들어지는 조합을 계산.
        k += 1 << types[mDestinations[i]];
    }
    if (myset[k].empty()) return -1;
    int city = myset[k].begin()->second;
    int a = dist[0][city], b = dist[1][city], c = dist[2][city];
    for (int i = 1; i <= 7; ++i) { // 1. 주택가격을 인상하므로 set으로부터 일단 제거
        int nd = (i & 1) * a + ((i >> 1) & 1) * b + ((i >> 2) & 1) * c;
        if (nd <= limit)
            myset[i].erase({ ((UI)price[city] << 17) | nd, city });
    }
    price[city]++; // 2. 주택가격 1인상
    for (int i = 1; i <= 7; ++i) { // 3. set에 다시 등록하기
        int nd = (i & 1) * a + ((i >> 1) & 1) * b + ((i >> 2) & 1) * c;
        if (nd <= limit) // 제한거리를 만족하는 경우만 추가 *****
            myset[i].insert({ ((UI)price[city] << 17) | nd, city });
    }
    return city;
}