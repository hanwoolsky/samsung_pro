#include<queue>
#include<set>
#include<math.h>
#include<string.h>
using namespace std;
using pii = pair<int, int>;

const int LM = 203;

int waitWorker;                    // 대기중인 관리 수
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
set<pii> expectSet;         // { -expectTax, cid } 작은 순 => 1) expectTax 큰 순, 2) cid 작은 순
set<pii>::iterator eit[LM];

void init(int N, int M) {
    waitWorker = M;
    eventPQ = {};
    expectSet.clear();
    for (int i = 0; i < N; i++) {
        storage[i] = expected[i] = used[i] = 0;
        eit[i] = expectSet.end();
    }
}

void updateExpectSet(int cid) {
    /* 등록돼 있는 경우 지우고 */
    if (eit[cid] != expectSet.end()) {
        expectSet.erase(eit[cid]);
        eit[cid] = expectSet.end();
    }
    /* 파견 가능한 경우에만 등록 */
    if (!used[cid] && expected[cid]) eit[cid] = expectSet.insert({ -expected[cid], cid }).first;
}

/* destTick까지 상황 진행 */
void update(int destTick) {
    while (eventPQ.size() && eventPQ.top().T <= destTick) {
        Data cur = eventPQ.top();
        eventPQ.pop();

        int type = cur.type, T = cur.T, cid = cur.cid, cnt = cur.cnt;

        if (type == EXPECT) {           // 예상곡물 추가
            expected[cid] += cnt;
            updateExpectSet(cid);
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
            updateExpectSet(cid);
            eventPQ.push({ SEND, T });
        }
        if (type == SEND) {             // 파견 가능한 관리 파견
            while (waitWorker && expectSet.size()) {
                int cid = expectSet.begin()->second;
                expectSet.erase(expectSet.begin());
                eit[cid] = expectSet.end();

                used[cid] = 1;
                waitWorker--;
                eventPQ.push({ ARRIVE, T + cid, cid });
            }
        }
    }
}

int order(int tStamp, int mCityA, int mCityB, int mTax) {
    int addT = tStamp + abs(mCityB - mCityA);        // 곡물이 추가되는 시각에 상황 추가
    eventPQ.push({ ADD, addT, mCityB, mTax });

    int expectT = max(tStamp, addT - mCityB);     // 예상곡물이 추가되는 시각에 상황 추가
    eventPQ.push({ EXPECT, expectT, mCityB, mTax });

    update(tStamp);                                     // tStamp까지 상황 진행
    return storage[0];
}

int check(int tStamp) {
    update(tStamp);
    return storage[0];
}

void destroy() {}