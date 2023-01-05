#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include<cstring>
#include <queue>
using namespace std;

const int SIZE = 6;
const int INF = 1000000000;
int price[SIZE]; // 최소 거리 배열
vector<pair<int, int>> graph[SIZE];// 노드 간선 정보 graph[srcnode] = {destnode, cost};

struct DATA {
    int node;
    int cost;
    bool operator<(const DATA& x) const {
        return cost > x.cost; // 나중에 들어온 애가 작으면 우선 순위가 높다 -> 위로 올려준다
    } // 작은 애가 우선 순위가 높아야 하므로 cost > x.cost가 맞다.
};

priority_queue<DATA> pq;

void dijkstra(int start) {
    pq.push({ 0, start });
    price[start] = 0; // start -> start = 0
    
    while (!pq.empty()) {
        int n = pq.top().node;
        int p = pq.top().cost;
        pq.pop();

        if (price[n] < p) continue; // 현재 노드가 이미 처리되었다는 의미
        for (int i = 0; i < graph[n].size(); i++) {
            int newn = graph[n][i].first;
            int newc = graph[n][i].second + p;
            if (price[newn] > newc) {
                price[newn] = newc;
                pq.push({ newn, newc });
            }
        }
        for (int i = 0; i < 6; i++) {
            printf("%d ", price[i]);
        }
        printf("\n");
    }
}

int main() {
    // pq 거리 INF로 설정
    for (int i = 0; i < 6; i++) {
        price[i] = INF;
    } // memset은 0 or 1로 초기화할 때만
    graph[0].push_back({ 1, 2 });
    graph[0].push_back({ 2, 5 });
    graph[0].push_back({ 3, 1 });
    graph[1].push_back({ 2, 3 });
    graph[1].push_back({ 4, 2 });
    graph[2].push_back({ 1, 3 });
    graph[2].push_back({ 5, 5 });
    graph[3].push_back({ 2, 3 });
    graph[3].push_back({ 4, 1 });
    graph[4].push_back({ 5, 2 });
    graph[4].push_back({ 2, 1 });

    dijkstra(0);

    return 0;
}