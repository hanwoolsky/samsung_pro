// 1. O(N^2) : 정점은 많지만 간선은 적을 때 비효율적
#include <stdio.h>

int vertex = 6;
int INF = 1000000000;

// 전체 그래프 초기화
int a[6][6] = {{0, 2, 5, 1, INF, INF}, {0, 2, 5, 1, INF, INF}, {0, 2, 5, 1, INF, INF}, {0, 2, 5, 1, INF, INF}, {0, 2, 5, 1, INF, INF}, {0, 2, 5, 1, INF, INF}};
bool v[6]; // 방문한 노드인가?
int d[6]; // 비용, 최단 거리 저장

// 방문하지 않은 노드 중 가장 최소 거리를 가지는 정점을 반환한다.
int getSmallIndex(){
  int min = INF;
  int index = 0;
  for (int i = 0; i<vertex; i++){
    if(d[i] < min && !v[i]){
      min = d[i];
      index = i;
    }
  }
  return index;
}

// 다익스트라
void dijkstra(int start){
  for(int i = 0; i < vertex; i++){
    d[i] = a[start][i]; // 시작점부터 모든 노드까지 비용 넣기
  }
  v[start] = true; // 시작점 방문 처리
  for(int i = 0; i < vertex - 2; i++){
    int current = getSmallIndex(); // 최소비용 노드 인덱스
    v[current] = true;
    for(int j = 0; j < 6; j++){
      if(!v[j]){ // 인접한 노드 중 방문하지 않은 노드
        if(d[current] + a[current][j] < d[j]){
          d[j] = d[current] + a[current][j];
        }
      }
    }
  }
}

// 2. O(NlogN)
#include <queue>
using namespace std;

struct DATA{
  int node;
  int cost;
  bool operator<(const DATA&x) const {
    return cost < x.cost; // 왜 오름차순이지?
  }
};

priority_queue<DATA> pq;