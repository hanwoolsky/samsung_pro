#define MAX_N 100
#include<queue>
#include<string.h>
using namespace std;
using pii = pair<int, int>;

int n;
int(*cost)[100];        // 에너지 소비량, 2차원 포인터
int bactCnt[3];         // 세균 개수(1=파랑, 2=빨강)
int bactMap[100][100];  // bactMap[r][c] = (1=파랑, 2=빨강, 0=비어있음)
pii que[10003];         // {r,c}
int dx[] = { -1,0,1,0 }, dy[] = { 0,1,0,-1 };
struct Data {
    int cost, r, c;
    bool operator<(const Data&R) const {
        if (cost != R.cost) return cost < R.cost;
        if (r != R.r) return r > R.r;
        return c > R.c;
    }
};
priority_queue <Data> pq;
bool visit[100][100];

void init(int N, int Dish[MAX_N][MAX_N])
{
    n = N;
    cost = Dish;
    memset(bactMap, 0, sizeof(bactMap));
    bactCnt[1] = bactCnt[2] = 0;
}

int dropMedicine(int target, int r, int c, int energy)
{
    r--, c--;
    if (bactMap[r][c] == 3 - target) return bactCnt[target]; // 다른 종류의 세균이 있는 경우, 종료
    else if (bactMap[r][c] == 0) {                           // 비어있는 경우, 생성
        bactCnt[target]++;
        energy -= cost[r][c];
        bactMap[r][c] = target;
    }
    
    pq = {};                            // pq 초기화
    memset(visit, 0, sizeof(visit));    // visit 초기화
    int head = 0, tail = 0;             // queue 초기화

    que[tail++] = { r, c };             // (r,c) 활성화
    visit[r][c] = 1;

    while (energy > 0) {                // 남은 번식에너지 있는 동안 반복
        while (head < tail) {           // queue가 빌 때까지 주변 활성화
            auto t = que[head++];       // front 값 기록, dequeue
            for (int i = 0; i < 4; i++) {
                r = t.first + dx[i], c = t.second + dy[i];
                if (r < 0 || r >= n || c < 0 || c >= n) continue;       // 범위 벗어나는 경우
                if (visit[r][c]) continue;                              // 이미 방문한 경우
                visit[r][c] = 1;                                        // 방문 처리
                if (bactMap[r][c] == 0) pq.push({ cost[r][c], r, c });  // 비어있는 경우, 번식 후보로 등록
                if (bactMap[r][c] == target)                            // 타겟 세균인 경우, 활성화
                    que[tail++] = { r,c };
            }
        }
        if (pq.empty()) break;              // 번식 가능 위치가 없는 경우, 종료
        auto t = pq.top(); pq.pop();        // 가장 우선순위 값 선택
        bactMap[t.r][t.c] = target;         // 생성
        que[tail++] = { t.r,t.c };          // 활성화                     
        bactCnt[target]++;                  // 개수 증가
        energy -= cost[t.r][t.c];           // 번식 에너지 감소
    }
    return bactCnt[target];
}

int cleanBacteria(int r, int c)
{
    r--, c--;
    int target = bactMap[r][c];
    if (!target) return -1;
    int head = 0, tail = 0;         // queue 초기화
    que[tail++] = { r,c };          // 실시간으로 소멸시켜가며 flood-fill
    bactMap[r][c] = 0;
    while (head < tail) {
        auto t = que[head++];
        for (int i = 0; i < 4; i++) {
            r = t.first + dx[i], c = t.second + dy[i];
            if (r < 0 || r >= n || c < 0 || c >= n) continue;
            if (bactMap[r][c] != target) continue; // 실시간으로 소멸시키므로 별도 visited check 필요 없음
            que[tail++] = { r,c };
            bactMap[r][c] = 0;
        }
    }
    return bactCnt[target] -= tail;    // 개수 한번에 감소 후 반환
}