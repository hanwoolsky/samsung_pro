#include<queue>
#include<math.h>
#include<string.h>
using namespace std;

const int LM = 203;

int N, waitWorker;                 // 도시 수, 대기중인 관리 수
int storage[LM], expected[LM];     // 곡물의 양, 예상 곡물의 양
bool used[LM];                     // 관리 파견 여부

enum TYPE {
    ADD,            // 곡물량 추가
    EXPECT,         // 예상 곡물량 추가
    ARRIVE,         // 관리 파견된 도시에 도착
    BACK,           // 관리 수도로 복귀
    SEND            // 파견 가능한 관리들 파견
};

struct Data {
    int type, T, cid, cnt;                       // 상황 종류, 발생 시각, 발생 도시, 곡물량
    bool operator<(const Data& r) const {
        if (T != r.T) return T > r.T;           // 1순위) 먼저 일어나고
        return type > r.type;                   // 2순위) type 번호가 작은 순
    }                                           //        EXPECT, BACK > SEND   |    ADD > ARRIVE
};
priority_queue<Data> eventPQ;

void init(int N, int M) {
    ::N = N, waitWorker = M;
    eventPQ = {};
    for (int i = 0; i < N; i++)
        storage[i] = expected[i] = used[i] = 0;
}

/* destTick까지 상황 진행 */
void update(int tStamp) {
    while (eventPQ.size() && eventPQ.top().T <= tStamp) {
        Data cur = eventPQ.top();
        eventPQ.pop();

        int type = cur.type, T = cur.T, cid = cur.cid, cnt = cur.cnt;

        if (type == EXPECT) {           // 예상곡물 추가
            expected[cid] += cnt;
            eventPQ.push({ SEND, T });
        }
        if (type == ADD) {              // 곡물 추가
            storage[cid] += cnt;
        }
        if (type == ARRIVE) {           // 관리 파견도시 도착
            eventPQ.push({ BACK, T + cid, cid, storage[cid] });
            expected[cid] -= storage[cid];
            storage[cid] = 0;
        }
        if (type == BACK) {             // 관리 수도 복귀
            waitWorker++;
            used[cid] = 0;
            storage[0] += cnt;
            eventPQ.push({ SEND, T });
        }
        if (type == SEND) {             // 파견 가능한 관리 파견
            while (waitWorker) {        // 파견될 관리 없는 경우 종료
                int cid = 0, maxCnt = 0;
                for (int i = 1; i < N; i++)
                    if (!used[i] && maxCnt < expected[i])
                        cid = i, maxCnt = expected[i];

                if (!cid) break;            // 파견될 도시 없는 경우 종료

                used[cid] = 1;              // cid 도시로 관리 파견
                waitWorker--;
                eventPQ.push({ ARRIVE, T + cid, cid });
            }
        }
    }
}

int order(int tStamp, int mCityA, int mCityB, int mTax) {
    int addT = tStamp + abs(mCityB - mCityA);        // 곡물이 추가되는 시각에 상황 추가
    eventPQ.push({ ADD, addT, mCityB, mTax });

    int expectT = max(tStamp, addT - mCityB);       // 예상곡물이 추가되는 시각에 상황 추가
    eventPQ.push({ EXPECT, expectT, mCityB, mTax });

    update(tStamp);                                     // tStamp까지 상황 진행
    return storage[0];
}

int check(int tStamp) {
    update(tStamp);
    return storage[0];
}

void destroy() {}