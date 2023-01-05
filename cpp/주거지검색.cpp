using namespace std;
#include <cstring> // memset
#include <unordered_map>
#include <algorithm> // min
#include <queue> // priority_queue
#define MAXN (3001)

unordered_map<int, int> hmap;
priority_queue<pair<int, int>> pq;
int shortdist[3][MAXN];
int dist[MAXN][MAXN];
int price[MAXN];
int mainCity[3];
int limit;
int city;
int INF = 1000000000;
int visited[MAXN];
vector<pair<int, int>> info[MAXN]; // => 구조 dist[start] = {(cost, end), (cost, end), ... }; // 나중에 struct로 두번째 우선순위 주는거 해보기

int getSmallIndeX(int start) {
    int minn = INF;
    int index = 0;
    for (int i = 0; i < city; i++) {
        if (shortdist[hmap[start]][i] < minn && !visited[i]) {
            minn = shortdist[hmap[start]][i];
            index = i;
        }
    }
    return index;
}

void dijkstra(int start) { // param : a, b, c
    shortdist[hmap[start]][hmap[start]] = 0;
    pq.push(make_pair(0, start)); // start -> start = 0

    while (!pq.empty()) {
        int cost = -pq.top().first;
        int destNode = pq.top().second;
        pq.pop();
        if (shortdist[hmap[start]][destNode] < cost) continue; // 기존 거리(s -> destNode 최단거리)가 이미 작다면(s -> destNode) 살필 필요 없음
        for (int i = 0; i < info[destNode].size(); i++) {
            int nextCost = info[destNode][i].first + cost;
            int nextNode = info[destNode][i].second;
            if (nextCost < shortdist[hmap[start]][nextNode]) {
                shortdist[hmap[start]][nextNode] = nextCost;
                pq.push({ -nextCost, nextNode });
            }
        }
    }
} // a -> b의 최소거리를 계속 바꾸어주어야 하기 때문에 vector 형태에 push할 수 없다. ==> 수정이 어려우므로 => 어차피 비용이 커지면 pop되므로 상관 없다.

void init(int N, int mDownTown[])
{
    city = N;
    for (int i = 0; i < 3; i++) {
        hmap[mDownTown[i]] = i; // hmap : a -> 0 b -> 1, c -> 2
        mainCity[i] = mDownTown[i]; // mainCity : 0 -> a, 1 -> b, 2 -> c
    }
    memset(shortdist, 0, sizeof(shortdist));
    memset(dist, 0, sizeof(dist));
}
void newLine(int M, int mCityIDs[], int mDistances[])
{
    for (int i = 0; i < M - 1; i++) {
        dist[mCityIDs[i]][mCityIDs[i + 1]] = min(dist[mCityIDs[i]][mCityIDs[i + 1]], mDistances[i]);
        dist[mCityIDs[i + 1]][mCityIDs[i]] = min(dist[mCityIDs[i]][mCityIDs[i + 1]], mDistances[i]);
        info[mCityIDs[i]].push_back({ mDistances[i], mCityIDs[i + 1] });
    }
}
void changeLimitDistance(int mLimitDistance)
{
    limit = mLimitDistance;
    for (int i = 0; i < 3; i++) {
        dijkstra(mainCity[i]);
    }
}
int findCity(int mOpt, int mDestinations[])
{
    int price, tmp, recom;
    int j = 0;
    price = 1e9;
    for (int i = 0; i < city; i++) {
        tmp = 0;
        for (j = 0; j < mOpt; j++) {
            tmp += shortdist[hmap[mDestinations[j]]][i];
        }
        if (tmp < limit && price > tmp) {
            price = tmp;
            recom = j;
        }
    }
    return j + 1;
}