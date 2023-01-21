extern void makeCookies(int mID);

#include <queue>
#include <list>
#define MAX_ORDER (20000)
#define MAX_SHAPE (1000)
#define MAX_CUTTER (100)
using namespace std;

struct ORDER {
    int shape; // 쿠키 모양
    int orderStart; // 주문 들어온 순서
    int orderFinish; // 수령일
    bool isMade; // 주문 처리 여부

    ORDER* init(int shapes, int orderStarts, int orderFinishs) {
        this->shape = shapes;
        this->orderStart = orderStarts;
        this->orderFinish = orderFinishs;
        this->isMade = false;
        return this;
    }
};

ORDER orderInfo[MAX_ORDER]; // 주문을 담을 배열
int orderIdx; // 주문 인덱스
int curDay; // 현재 날짜
int orderSeq; // 주문 순서

struct COMP {
    bool operator()(ORDER* a, ORDER* b) {
        return a->orderFinish != b->orderFinish ? a->orderFinish > b->orderFinish : a->orderStart > b->orderStart;
    }
};
priority_queue<ORDER*, vector<ORDER*>, COMP> allOrderPq; // 전체 주문(의 주소)을 관리하는 PQ, 우선 순위 : orderFinish가 작고 orderStart가 작은 것
priority_queue<ORDER*, vector<ORDER*>, COMP> shapePq[MAX_SHAPE + 1]; // shape 별 주문(의 주소)을 관리하는 PQ, 우선 순위 : 위와 같다.

list<int> cutterShape[MAX_CUTTER + 1]; // mID별 만들 수 있는 모양 리스트
list<int> shapeCutter[MAX_SHAPE + 1]; // 모양별 자신을 만들 수 있는 mID


void init(void){
    orderIdx = curDay = 0;
    orderSeq = 0;
    allOrderPq = {};
    for (int i = 0; i <= MAX_SHAPE; i++) {
        shapePq[i] = {};
        shapeCutter[i].clear();
    }
    for (int i = 0; i <= MAX_CUTTER; i++) cutterShape[i].clear();
}

void addCookieCutter(int mID, int N, int mShapeList[]){
    for (int i = 0; i < N; i++) {
        cutterShape[mID].push_back(mShapeList[i]);
        shapeCutter[mShapeList[i]].push_back(mID);
    }
}

void orderCookie(int mShape, int daysLeft) {
    ORDER* order = orderInfo[orderIdx++].init(mShape, orderSeq++, curDay + daysLeft); // 주문 순서 대신 주문한 날짜 curDay를 넣어 같은 날짜의 구분을 못해서 3개 fail
    allOrderPq.push(order);
    shapePq[mShape].push(order);
}

int checkRemain(int mShape){
    return shapePq[mShape].size();
}

int findMid() {
    int makeShape = allOrderPq.top()->shape; // 만들어야할 쿠키
    int cnt;
    int maxCnt = 0;
    int mID = 100;
    auto mit = shapeCutter[makeShape].begin();
    auto cit = cutterShape[*mit].begin();
    for (mit = shapeCutter[makeShape].begin(); mit != shapeCutter[makeShape].end(); mit++) { // 해당 쿠키를 만들 수 있는 틀들
        cnt = 0;
        for (cit = cutterShape[*mit].begin(); cit != cutterShape[*mit].end(); cit++) {
            if (shapePq[*cit].size()) cnt++;
        }
        if (maxCnt < cnt) {
            maxCnt = cnt;
            mID = *mit;
        }
        else if (maxCnt == cnt) {
            if (mID > *mit) mID = *mit;
        }
    }
    return mID;
}

void newDay(void){
    curDay++;
    while (!allOrderPq.empty() && allOrderPq.top()->orderFinish == curDay) {
        if (allOrderPq.top()->isMade == true) allOrderPq.pop();
        else {
            int mID = findMid(); // 주문을 많이 처리할 수 있는 틀 고르기
            makeCookies(mID);
            // 주문 처리 && mID로 만들어진 쿠키들 전부 제거
            allOrderPq.pop();
            for (auto cit = cutterShape[mID].begin(); cit != cutterShape[mID].end(); cit++) {
                if (shapePq[*cit].size()) {
                    ORDER* order = shapePq[*cit].top();
                    order->isMade = true;
                    shapePq[*cit].pop();
                }
            }
        }
    }
}
