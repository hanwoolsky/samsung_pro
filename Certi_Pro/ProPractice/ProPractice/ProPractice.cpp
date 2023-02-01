#if 0
/***********************************************************/
// [병사관리] : 나의 풀이
/***********************************************************/
#include <unordered_set>
#include <unordered_map>
#include <cstring>

using namespace std;

const int SIZE = 100000;
int soldScore[SIZE + 1];
int teamScore[5];
unordered_set<int> ids[5];
unordered_map<int, int> hmap;


void init(){
    memset(soldScore, 0, sizeof(soldScore));
    memset(teamScore, 0, sizeof(teamScore));
    for (int i = 0; i < 5; i++) ids[i].clear();
    hmap.clear();
}

void hire(int mID, int mTeam, int mScore){
    ids[mTeam - 1].insert(mID);
    soldScore[mID] = mScore - teamScore[mTeam - 1]; // bestSoldier에서 teamSocre[mTeam-1]이 더해질테니 빼두기
    hmap.insert({ mID, mTeam - 1 });
}

void fire(int mID){
    ids[hmap[mID]].erase(mID);
}

void updateSoldier(int mID, int mScore){
    soldScore[mID] = mScore;
}

void updateTeam(int mTeam, int mChangeScore){
    teamScore[mTeam - 1] += mChangeScore;
}

int bestSoldier(int mTeam){
    int maxScore = -5;
    int id = 0;

    for (auto it = ids[mTeam - 1].begin(); it != ids[mTeam - 1].end(); it++) {
        int score = soldScore[*it] + teamScore[mTeam - 1];
        if (score > 5) score = 5;
        else if (score < 1) score = 1;
        soldScore[*it] = score;
        if (maxScore < score) {
            maxScore = score;
            id = *it;
        }
        else if (maxScore == score) {
            if (id < *it) id = *it;
        }
    }
    teamScore[mTeam - 1] = 0;

    return id;
}

int main()
{
    init();
    hire(16, 1, 5);
    hire(21, 1, 5);
    bestSoldier(1);
    fire(21);
    bestSoldier(1);
    hire(25, 1, 4);
    hire(30, 1, 2);
    updateTeam(1, 1);
    bestSoldier(1);
    updateTeam(1, 2);
    bestSoldier(1);
    updateSoldier(30, 2);
    bestSoldier(1);
    updateTeam(1, -4);
    hire(1, 1, 3);
    updateTeam(1, -1);
    bestSoldier(1);
    hire(100000, 5, 1);
    bestSoldier(5);
}

// 결론 : updateTeam(2) + updateTeam(-2) != updateTeam(0)이므로 바로 update를 해주어야한다. => 효율적인 다른 알고리즘을 찾아야한다.
#endif

#if 0
#include <stdio.h>
/***********************************************************/
// [병사관리] : 나의 풀이 - 강사님 아이디어 들은 후 1307ms
/***********************************************************/
#include <list>
#include <unordered_map>

using namespace std;

struct DATA {
    int teamNum;
    int isfire; // 1 -> fire
    int seqNum;
};

struct listData {
    int idNum;
    int seqNum;
};

list<listData> soldScore[6][6];
unordered_map<int, DATA> hmap;

void init() {
    hmap.clear();
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            soldScore[i][j].clear();
        }
    }
}

void hire(int mID, int mTeam, int mScore) {
    auto it = hmap.find(mID);
    if (it != hmap.end()) { // fire 된 후에 hire되는 경우
        hmap[mID].isfire = 0;
        soldScore[mTeam][mScore].push_back({ mID, ++hmap[mID].seqNum });
    }
    else {
        hmap.insert({ mID, {mTeam, 0, 0} });
        soldScore[mTeam][mScore].push_back({ mID, 0 });
    }
}

void fire(int mID) {
    hmap[mID].isfire = 1;
}

void updateSoldier(int mID, int mScore) {
    soldScore[hmap[mID].teamNum][mScore].push_back({ mID, ++hmap[mID].seqNum });
}

void updateTeam(int mTeam, int mChangeScore) {
    int newScore = 0;
    if (mChangeScore < 0) {
        for (int i = 2; i < 6; i++) {
            newScore = i + mChangeScore;
            if (newScore < 1) newScore = 1;
            auto it = soldScore[mTeam][newScore].end();
            soldScore[mTeam][newScore].splice(it, soldScore[mTeam][i]);
        }
    }
    else if (mChangeScore > 0) {
        for (int i = 4; i > 0; i--) {
            newScore = i + mChangeScore;
            if (newScore > 5) newScore = 5;
            auto it = soldScore[mTeam][newScore].end();
            soldScore[mTeam][newScore].splice(it, soldScore[mTeam][i]);
        }
    }
}

int bestSoldier(int mTeam) {
    int i = 5;
    int id = 0;
    int flag = 0;
    for (int i = 5; i > 0; i--) {
        if (soldScore[mTeam][i].size()) {
            for (auto it = soldScore[mTeam][i].begin(); it != soldScore[mTeam][i].end();) {
                if (it->seqNum != hmap[it->idNum].seqNum) it = soldScore[mTeam][i].erase(it);
                else if (hmap[it->idNum].isfire) it = soldScore[mTeam][i].erase(it); // else 안 넣으면 틀림
                else if (it->idNum > id) {
                    flag = 1;
                    id = it->idNum;
                    it++;
                }
                else it++;
            }
            if (flag) break;
        }
    }

    return id;
}
#endif

#if 0
/***********************************************************/
// [병사관리] : 강사님의 풀이 464ms
/***********************************************************/
#include <list>

using namespace std;

#define MAX_SCORE (5)
#define MAX_TEAM (5)
#define MAX_ID  (100000)

struct LENTRY {
    int id;    int seq;
    LENTRY(int id, int seq) {
        this->id = id; this->seq = seq;
    }
};

struct MERCENARY {
    int mTeam;
    bool fired;
    int seq;
};

struct TEAM {
    list <LENTRY> list_score[MAX_SCORE + 1];
    void init() {
        for (int i = 0; i <= MAX_SCORE; i++) {
            list_score[i].clear();
        }
    }
};

MERCENARY mercenary[MAX_ID + 1];
TEAM teams[MAX_TEAM + 1];
int seqnum = 0;
void init()
{
    for (int i = 1; i <= MAX_ID; i++) {
        mercenary[i].fired = true;
    }

    for (int i = 1; i <= MAX_TEAM; i++) {
        teams[i].init();
    }
    seqnum = 0;
}

void hireMercenary(int mID, int mTeam, int mScore) {
    mercenary[mID].mTeam = mTeam;
    mercenary[mID].seq = ++seqnum;
    mercenary[mID].fired = false;
    teams[mTeam].list_score[mScore].push_back({ mID, mercenary[mID].seq });
}

void fireMercenary(int mID) {
    mercenary[mID].fired = true;
}

void updateMercenaryScore(int mID, int mScore)
{
    int mTeam = mercenary[mID].mTeam;
    mercenary[mID].seq = ++seqnum;
    teams[mTeam].list_score[mScore].push_back({ mID, mercenary[mID].seq });
}

void updateTeamScore(int mTeam, int mChangeScore)
{
    if (mChangeScore == 0) return;
    if (mChangeScore > 0) {
        for (int i = 4; i >= 1; i--) {
            int target = i + mChangeScore;
            if (target > 5) target = 5;
            teams[mTeam].list_score[target].splice(teams[mTeam].list_score[target].end(), teams[mTeam].list_score[i]);
        }
    }
    else {
        for (int i = 2; i <= 5; i++) {
            int target = i + mChangeScore;
            if (target < 1) target = 1;
            teams[mTeam].list_score[target].splice(teams[mTeam].list_score[target].end(), teams[mTeam].list_score[i]);
        }
    }
}

int bestMercenary(int mTeam)
{
    int ret = -1;
    for (int i = 5; i >= 1; i--) {
        auto iter = teams[mTeam].list_score[i].begin();
        while (iter != teams[mTeam].list_score[i].end()) {
            if (!mercenary[(*iter).id].fired && mercenary[(*iter).id].seq == (*iter).seq) {
                if (ret < (*iter).id) ret = (*iter).id;
                iter++;
            }
            else {
                iter = teams[mTeam].list_score[i].erase(iter);
            }
        }
        if (ret != -1) break;
    }
    return ret;
}
#endif

#if 0
/***********************************************************/
// [여행상품추천] : 강사님의 풀이
/***********************************************************/
#include <queue>
#include <list>
#include <unordered_map>

using namespace std;

#ifndef NULL
#define NULL 0
#endif

#define MAX_USERID        (1000)
#define MAX_BUDDY           (21)
#define MAX_AREA            (10)
#define MAX_PROD            (40000)

struct USER
{
    int cnt_area[MAX_AREA + 1];
    list<int> list_buddy;
    void init() {
        for (int i = 1; i <= MAX_AREA; i++) cnt_area[i] = 0;
        list_buddy.clear();
    }
};
USER user[MAX_USERID + 1];

struct PROD
{
    int prod_id;
    int area;
    int price;
    bool booking;
    bool operator>(const PROD& d) {
        if (price == d.price) return prod_id > d.prod_id;
        return price > d.price;
    }


    PROD* init(int prod_id, int area, int price) {
        this->prod_id = prod_id;
        this->area = area;
        this->price = price;
        this->booking = false;
        return this;
    }
};


struct COMP_PRODP {
    bool operator()(PROD* a, PROD* b) {
        if (a->price == b->price) return a->prod_id > b->prod_id;
        return a->price > b->price;
    }
};

priority_queue<PROD*, vector<PROD*>, COMP_PRODP> pq_area[MAX_AREA + 1];

PROD alloc_prod[MAX_PROD];
int prod_cnt;

unordered_map<int, PROD*> ht;

void init(int N, int M) {
    prod_cnt = 0;
    for (int i = 1; i <= MAX_USERID; i++) user[i].init();
    for (int i = 1; i <= MAX_AREA; i++) pq_area[i] = {};
    ht.clear();
}

void befriend(int uid1, int uid2) {
    user[uid1].list_buddy.push_back(uid2);
    user[uid2].list_buddy.push_back(uid1);
}

void add(int pid, int area, int price) {
    PROD* prod;
    prod = alloc_prod[prod_cnt++].init(pid, area, price);

    pq_area[area].push(prod);
    ht.insert({ pid,prod });
}

void reserve(int uid, int pid) {
    PROD* prod;

    auto it = ht.find(pid);
    if (it == ht.end()) return;

    prod = it->second;

    user[uid].cnt_area[prod->area]++;
    prod->booking = true;
}

int recommend(int uid) {
    int i, j, buddy_id;
    int tf = 0, tp = 0;
    int cnt_area[MAX_AREA + 1];
    int max_cnt_area = -1;
    PROD adv = { 0x7fffffff,0x7fffffff,0x7fffffff,false };

    for (j = 1; j <= MAX_AREA; j++)
        cnt_area[j] = user[uid].cnt_area[j];


    for (int buddy_id : user[uid].list_buddy) {
        for (j = 1; j <= MAX_AREA; j++)
            cnt_area[j] += user[buddy_id].cnt_area[j];
    }

    for (i = 1; i <= MAX_AREA; i++)
    {
        while (!pq_area[i].empty() && pq_area[i].top()->booking) {
            pq_area[i].pop();
        }
        if (pq_area[i].empty()) continue;
        if ((max_cnt_area < cnt_area[i])
            || ((max_cnt_area == cnt_area[i]) && (adv > *pq_area[i].top()))) {
            max_cnt_area = cnt_area[i];
            adv = *pq_area[i].top();
        }
    }

    return adv.prod_id;
}
#endif


#if 0
/***********************************************************/
// [시간여행자의주식]
/***********************************************************/
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define CMD_INIT 1
#define CMD_BUY 2
#define CMD_SELL 3
#define CMD_CANCEL 4
#define CMD_BEST_PROFIT 5

extern void init();
extern int buy(int mNumber, int mStock, int mQuantity, int mPrice);
extern int sell(int mNumber, int mStock, int mQuantity, int mPrice);
extern void cancel(int mNumber);
extern int bestProfit(int mStock);

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

static bool run()
{
    int numQuery;

    int mNumber, mStock, mQuantity, mPrice;

    int userAns, ans;

    bool isCorrect = false;

    scanf("%d", &numQuery);

    for (int i = 0; i < numQuery; ++i)
    {
        int cmd;
        scanf("%d", &cmd);
        switch (cmd)
        {
        case CMD_INIT:
            init();
            isCorrect = true;
            break;
        case CMD_BUY:
            scanf("%d %d %d %d", &mNumber, &mStock, &mQuantity, &mPrice);
            userAns = buy(mNumber, mStock, mQuantity, mPrice);
            scanf("%d", &ans);
            if (userAns != ans)
            {
                isCorrect = false;
            }
            break;
        case CMD_SELL:
            scanf("%d %d %d %d", &mNumber, &mStock, &mQuantity, &mPrice);
            userAns = sell(mNumber, mStock, mQuantity, mPrice);
            scanf("%d", &ans);
            if (userAns != ans)
            {
                isCorrect = false;
            }
            break;
        case CMD_CANCEL:
            scanf("%d", &mNumber);
            cancel(mNumber);
            break;
        case CMD_BEST_PROFIT:
            scanf("%d", &mStock);
            userAns = bestProfit(mStock);
            scanf("%d", &ans);
            if (userAns != ans)
            {
                isCorrect = false;
            }
            break;
        default:
            isCorrect = false;
            break;
        }
    }

    return isCorrect;
}

int main()
{
    setbuf(stdout, NULL);
    //freopen("sample_input.txt", "r", stdin);

    int T, MARK;
    scanf("%d %d", &T, &MARK);

    for (int tc = 1; tc <= T; tc++)
    {
        int score = run() ? MARK : 0;
        printf("#%d %d\n", tc, score);
    }

    return 0;
}

#include <queue>
#include <cstring>

#define MAX_STOCK     (5)
#define MAX_NUMBER   (200000)

using namespace std;

struct STOCK {
    int sid;
    int quantity;
    int price;
};

struct BUYCOMP {
    bool operator()(STOCK& x, STOCK& y) {
        return x.price != y.price ? x.price > y.price : x.sid > y.sid;
    }
};

struct SELLCOMP {
    bool operator()(STOCK& x, STOCK& y) {
        return x.price != y.price ? x.price < y.price : x.sid > y.sid;
    }
};

struct BSLIST {
    priority_queue<STOCK, vector<STOCK>, BUYCOMP> buyPQ; // 미체결 매도 주문
    priority_queue<STOCK, vector<STOCK>, SELLCOMP> sellPQ; // 미체결 매수 주문
    void init() {
        buyPQ = {};
        sellPQ = {};
    }
};

struct SUCCESS {
    int bidPrice[MAX_NUMBER + 1];
    int idx;
    int min_value;
    int max_benefit;
    void init() {
        memset(bidPrice, 0, sizeof(bidPrice));
        idx = 0;
        min_value = 1000000;
        max_benefit = 0;
    }
};

BSLIST typeList[MAX_STOCK + 1];
bool cancled[MAX_NUMBER + 1];
SUCCESS stockBid[MAX_STOCK + 1]; // bid, min

void init(){
    for (int i = 1; i <= MAX_STOCK; i++) {
        typeList[i].init();
        stockBid[i].init();
    }
    memset(cancled, 0, sizeof(cancled));
}

int buy(int mNumber, int mStock, int mQuantity, int mPrice){
    STOCK stock;
    while (!typeList[mStock].buyPQ.empty() && mQuantity) {
        stock = typeList[mStock].buyPQ.top();
        if (cancled[stock.sid]) typeList[mStock].buyPQ.pop();
        else if (stock.price > mPrice) {
            typeList[mStock].sellPQ.push({ mNumber, mQuantity, mPrice });
            return mQuantity; // break 넣으면 밑에서 또 push돼서 틀림
        }
        else {
            stockBid[mStock].bidPrice[stockBid[mStock].idx] = stock.price;
            if (stockBid[mStock].min_value > stock.price) stockBid[mStock].min_value = stock.price;
            else if (stockBid[mStock].max_benefit < stock.price - stockBid[mStock].min_value) stockBid[mStock].max_benefit = stock.price - stockBid[mStock].min_value;
            stockBid[mStock].idx += 1;

            typeList[mStock].buyPQ.pop();
            if (mQuantity < stock.quantity) {
                typeList[mStock].buyPQ.push({ stock.sid, stock.quantity - mQuantity, stock.price });
                mQuantity = 0;
            }
            else {
                mQuantity -= stock.quantity;
            }
        }
    }
    if (mQuantity != 0) typeList[mStock].sellPQ.push({ mNumber, mQuantity, mPrice });
    printf("%d\n", mQuantity);
    return mQuantity;
}

int sell(int mNumber, int mStock, int mQuantity, int mPrice) {
    STOCK stock;
    while (!typeList[mStock].sellPQ.empty() && mQuantity) {
        stock = typeList[mStock].sellPQ.top();
        if (cancled[stock.sid]) typeList[mStock].sellPQ.pop();
        else if (stock.price < mPrice) {
            typeList[mStock].buyPQ.push({ mNumber, mQuantity, mPrice });
            return mQuantity;
        }
        else {
            stockBid[mStock].bidPrice[stockBid[mStock].idx] = stock.price;
            if (stockBid[mStock].min_value > stock.price) stockBid[mStock].min_value = stock.price;
            else if (stockBid[mStock].max_benefit < stock.price - stockBid[mStock].min_value) stockBid[mStock].max_benefit = stock.price - stockBid[mStock].min_value;
            stockBid[mStock].idx += 1;
            typeList[mStock].sellPQ.pop();
            if (mQuantity < stock.quantity) {
                typeList[mStock].sellPQ.push({ stock.sid, stock.quantity - mQuantity, stock.price });
                mQuantity = 0;
            }
            else {
                mQuantity -= stock.quantity;
            }
        }
    }
    if(mQuantity != 0) typeList[mStock].buyPQ.push({ mNumber, mQuantity, mPrice }); // 0이 아닐 때 조건 안 넣으면 틀림
    printf("%d\n", mQuantity);
    return mQuantity;
}

void cancel(int mNumber){
    cancled[mNumber] = 1;
}

int bestProfit(int mStock){
    printf("%d\n", stockBid[mStock].max_benefit);
    return stockBid[mStock].max_benefit;
}
#endif


#if 0
/***********************************************************/
// [시간여행자의주식] : 강사님의 풀이
/***********************************************************/
#include <queue>

using namespace std;

#define MAX_ORDER (200000)
#define MAX_CRYPTO (5)

struct ORDER {
    int num;
    int amount;
    int price;
    bool canceled;

    ORDER* init(int num, int amount, int price) {
        this->num = num;
        this->amount = amount;
        this->price = price;
        this->canceled = false;
        return this;
    }
};

ORDER order[MAX_ORDER + 1];

struct COMP_BUY {
    bool operator()(ORDER* a, ORDER* b) {
        if (a->price == b->price) return a->num > b->num;
        else return a->price < b->price;
    }
};

struct COMP_SELL {
    bool operator()(ORDER* a, ORDER* b) {
        if (a->price == b->price) return a->num > b->num;
        else return a->price > b->price;
    }
};

typedef priority_queue <ORDER*, vector<ORDER*>, COMP_BUY> PQ_BUY;
typedef priority_queue <ORDER*, vector<ORDER*>, COMP_SELL> PQ_SELL;

struct CRYPTO {
    PQ_BUY pq_buy;
    PQ_SELL pq_sell;
    int min_price;
    int max_benefit;
    void init(void) {
        pq_buy = {};
        pq_sell = {};
        min_price = 10000000;
        max_benefit = 0;
    }
};

CRYPTO cr[MAX_CRYPTO + 1];

void init() {
    for (int i = 1; i <= MAX_CRYPTO; i++) {
        cr[i].init();
    }
}

inline int MIN(int a, int b) { return a < b ? a : b; }
inline int MAX(int a, int b) { return a > b ? a : b; }

int buyCoin(int num, int crypto, int amount, int price) {
    ORDER* porder = order[num].init(num, amount, price);
    PQ_SELL& pq_sell = cr[crypto].pq_sell;

    while (porder->amount > 0 && !pq_sell.empty() && pq_sell.top()->price <= porder->price) {
        ORDER* psell = pq_sell.top();
        if (psell->canceled) {
            pq_sell.pop();
            continue;
        }

        int price_sign = psell->price;

        if (cr[crypto].max_benefit < price_sign - cr[crypto].min_price)
            cr[crypto].max_benefit = price_sign - cr[crypto].min_price;

        if (cr[crypto].min_price > price_sign)
            cr[crypto].min_price = price_sign;

        int cnt_sign = MIN(porder->amount, psell->amount);

        porder->amount -= cnt_sign;
        psell->amount -= cnt_sign;

        if (psell->amount == 0) pq_sell.pop();
    }

    if (porder->amount > 0) cr[crypto].pq_buy.push(porder);

    return porder->amount;
}


int sellCoin(int num, int crypto, int amount, int price) {
    ORDER* porder = order[num].init(num, amount, price);
    PQ_BUY& pq_buy = cr[crypto].pq_buy;

    while (porder->amount > 0 && !pq_buy.empty() && pq_buy.top()->price >= porder->price) {
        ORDER* pbuy = pq_buy.top();
        if (pbuy->canceled) {
            pq_buy.pop();
            continue;
        }

        int price_sign = pbuy->price;
        int benefit = price_sign - cr[crypto].min_price;

        if (cr[crypto].max_benefit < benefit)
            cr[crypto].max_benefit = benefit;

        if (cr[crypto].min_price > price_sign)
            cr[crypto].min_price = price_sign;

        int cnt_sign = MIN(porder->amount, pbuy->amount);

        porder->amount -= cnt_sign;
        pbuy->amount -= cnt_sign;

        if (pbuy->amount == 0) pq_buy.pop();
    }

    if (porder->amount > 0) cr[crypto].pq_sell.push(porder);

    return porder->amount;
}

void cancelCoin(int num) {
    order[num].canceled = true;
}

int getBest(int crypto)
{
    return cr[crypto].max_benefit;
}
#endif


#if 0
/***********************************************************/
// [자전거 대여소] : 나의 풀이 - 대여소 넘나들어 반납을 보지 못함
/***********************************************************/
#include <stdio.h>
#include <unordered_map>
#include <queue>

#define MAXBIC      20000
#define MAXNum      10000
#define MAXN		100
#define MAXL		8

using namespace std;

struct USER {
    int TicketStart;
    int TicketFinish;
    int rentStart;
    int rentedidx;
};

unordered_map<string, USER> userMap;

struct BICYCLE {
    int curTime;
    int operTime;
    bool rented;
};

struct BIC {
    int bicNum;
    int validNum;
    vector<BICYCLE> bicStatus;
    void init() {
        bicStatus.clear();
        bicNum = 0;
        validNum = 0;
    }
};
BIC bicyclePQ[MAXN + 1];

int deliverTime[MAXN + 1];
int durTime;
int totalBicycle;

void init(int N, int durableTime, int deliveryTimes[MAXN]){
    userMap.clear();
    durTime = durableTime;
    totalBicycle = N;
    for (int i = 0; i < N; i++) deliverTime[i] = deliveryTimes[i];
    for (int i = 0; i < MAXN; i++) bicyclePQ[i].init();
}

void addBicycle(int cTimestamp, int pID, int bicycleNum){
    bicyclePQ[pID].bicNum += bicycleNum;
    bicyclePQ[pID].validNum += bicycleNum;
    while (bicycleNum--) {
        bicyclePQ[pID].bicStatus.push_back({ cTimestamp, 0 });
    }
    printf("add 대여소 %d에 자전거 개수 %d\n", pID, bicyclePQ[pID].bicNum);
}

void buyTimeet(int cTimestamp, char uName[MAXL], int validTime){
    auto it = userMap.find(uName);
    if (it == userMap.end()) userMap.insert({ uName, {cTimestamp, cTimestamp + validTime - 1, -1, -1} });
    else {
        if (it->second.ticketFinish < cTimestamp) {
            userMap[uName].ticketStart = cTimestamp;
            userMap[uName].ticketFinish = cTimestamp + validTime - 1;
        }
        else {
            userMap[uName].ticketFinish += validTime;
        }
    }
}

int rentBicycle(int cTimestamp, char uName[MAXL], int pID){
    auto it = userMap.find(uName);
    // 티켓을 구매한 적 없거나 유효기간이 지나거나 돌려주지 않거나 남아있지 않음
    if (it == userMap.end() || it->second.ticketFinish < cTimestamp || it->second.rentedidx >= 0 || !bicyclePQ[pID].validNum) {
        printf("rent %d\n", -1);  return -1;
    }
    printf("대여소 %d에 자전거 개수 %d\n", pID, bicyclePQ[pID].bicNum);
    int minOper = 1000000000;
    int idx = -1;
    for (int i = 0; i < bicyclePQ[pID].bicNum; i++) {
        printf("운행 시간 %d ", bicyclePQ[pID].bicStatus[i].operTime);
        if (bicyclePQ[pID].bicStatus[i].curTime > cTimestamp || bicyclePQ[pID].bicStatus[i].rented) continue;
        if (bicyclePQ[pID].bicStatus[i].operTime < minOper) {
            minOper = bicyclePQ[pID].bicStatus[i].operTime;
            idx = i;
        }
    }
    userMap[uName].rentStart = cTimestamp;
    userMap[uName].rentedidx = idx;
    bicyclePQ[pID].bicStatus[idx].rented = true;
    bicyclePQ[pID].validNum--;
    
    printf("\nrent %d\n", minOper);
    return minOper;
}

int returnBicycle(int cTimestamp, char uName[MAXL], int pID){
    int overtime = 0;

    auto it = userMap.find(uName);
    if (it == userMap.end() || it->second.rentedidx == -1) { printf("return %d\n", -1); return -1; }
    if (it->second.ticketFinish < cTimestamp) overtime = cTimestamp - it->second.ticketFinish;

    bicyclePQ[pID].bicStatus[it->second.rentedidx].operTime += cTimestamp - it->second.rentStart;
    bicyclePQ[pID].bicStatus[it->second.rentedidx].curTime = cTimestamp;
    bicyclePQ[pID].bicStatus[it->second.rentedidx].rented = false;
    bicyclePQ[pID].validNum++;
    if (bicyclePQ[pID].bicStatus[it->second.rentedidx].operTime > durTime) {
        bicyclePQ[pID].bicStatus[it->second.rentedidx].curTime = cTimestamp + deliverTime[pID];
        bicyclePQ[pID].bicStatus[it->second.rentedidx].operTime = 0;
    }

    printf("return %d\n", overtime);
    return overtime;
}
#endif


#if 0
/***********************************************************/
// [자전거 대여소] : 강사님의 풀이
/***********************************************************/
#include <deque>
#include <queue>
#include <unordered_map>
#include <string>

using namespace std;

#define MAX_CALL (100000)
#define MAX_USER (10000)

#define MAX_N        (100)
#define MAX_L        (8)

int totalBicycle;
int durTime;

struct BICYCLE
{
    int operTime;
    int cnt;
    BICYCLE* init(int operTime, int cnt) {
        this->operTime = operTime;
        this->cnt = cnt;
        return this;
    }
};

struct COMP_BICYCLE {
    bool operator()(BICYCLE* a, BICYCLE* b) {
        return a->operTime > b->operTime;
    }
};

int cnt_bicycle;
BICYCLE bicycle[MAX_CALL];

struct RENTAL {
    int repairTime;
    priority_queue<BICYCLE*, vector<BICYCLE*>, COMP_BICYCLE> pq_bicycle;
    deque<int> new_bicycle;

    int get_new_from_queue(int cTimestamp) {
        int cnt = 0;
        while (!new_bicycle.empty() && new_bicycle.front() <= cTimestamp) {
            cnt += 1;
            new_bicycle.pop_front();
        }
        return cnt;
    }

    void init(int repairTime) {
        this->repairTime = repairTime;
        this->pq_bicycle = {};
        this->new_bicycle.clear();
    }
};

RENTAL rental[MAX_N];

struct USER {
    int valid;
    int rentTime;
    int operTime;

    USER* init(int cTimestamp, int valid) {
        this->valid = cTimestamp + valid - 1;
        this->operTime = -1;
        this->rentTime = -1;
        return this;
    }
};

int cnt_user;
USER user[MAX_USER];
unordered_map<string, USER*> ht_user;

void init(int N, int durableTime, int deliveryTimes[]) {
    totalBicycle = N;
    durTime = durableTime;
    cnt_bicycle = cnt_user = 0;
    ht_user.clear();
    for (int n = 0; n < totalBicycle; n++) {
        rental[n].init(deliveryTimes[n]);
    }
}

void addBicycle(int cTimestamp, int pID, int bicycleNum) {
    int cnt = 0;
    bicycleNum += rental[pID].get_new_from_queue(cTimestamp);
    BICYCLE* pbicycle = bicycle[cnt_bicycle++].init(0, bicycleNum);
    rental[pID].pq_bicycle.push(pbicycle);
}

void buyTicket(int cTimestamp, char uName[], int validTime) {
    auto it = ht_user.find(uName);
    USER* puser;
    if (it == ht_user.end()) {
        puser = user[cnt_user++].init(cTimestamp, validTime);
        ht_user.insert({ uName, puser });
    }
    else {
        puser = it->second;
        if (cTimestamp > puser->valid) {
            puser->valid = cTimestamp + validTime - 1;
        }
        else puser->valid += validTime;
    }
}

int rentBicycle(int cTimestamp, char uName[], int bid) {
    auto it_user = ht_user.find(uName);
    if (it_user == ht_user.end()) return -1;

    USER* puser = it_user->second;
    if (puser->rentTime != -1) return -1;
    if (puser->valid < cTimestamp) return -1;

    int cnt = rental[bid].get_new_from_queue(cTimestamp);
    if (cnt > 0) {
        BICYCLE* pbicycle = bicycle[cnt_bicycle++].init(0, cnt);
        rental[bid].pq_bicycle.push(pbicycle);
    }

    if (rental[bid].pq_bicycle.empty()) return -1;

    puser->rentTime = cTimestamp;
    puser->operTime = rental[bid].pq_bicycle.top()->operTime;
    rental[bid].pq_bicycle.top()->cnt--;
    if (rental[bid].pq_bicycle.top()->cnt == 0) {
        rental[bid].pq_bicycle.pop();
    }

    return puser->operTime;
}

int returnBicycle(int cTimestamp, char uName[], int pID) {
    int usingTime;
    auto it_user = ht_user.find(uName);
    if (it_user == ht_user.end()) return -1;

    USER* puser = it_user->second;
    if (puser->rentTime == -1) return -1;

    usingTime = cTimestamp - puser->rentTime;
    puser->operTime += usingTime;
    if (puser->operTime > durTime) {
        rental[pID].new_bicycle.push_back(cTimestamp + rental[pID].repairTime);
    }
    else {
        BICYCLE* pbicycle = bicycle[cnt_bicycle++].init(puser->operTime, 1);
        rental[pID].pq_bicycle.push(pbicycle);
    }

    int overTime = cTimestamp - puser->valid;
    if (overTime < 0) overTime = 0;

    puser->rentTime = -1;

    return overTime;
}
#endif


#if 0
/***********************************************************/
// [쿠키 상점] : 1300ms
/***********************************************************/
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define MAX_N				10
#define MAX_ORDER			20000

extern void init(void);
extern void addCookieCutter(int mID, int N, int mShapeList[]);
extern void orderCookie(int mShape, int daysLeft);
extern int  checkRemain(int mShape);
extern void newDay(void);

/////////////////////////////////////////////////////////////////////////

static int mIDList[MAX_ORDER];
static int mIDCnt;

void makeCookies(int mID)
{
    if (mIDCnt >= MAX_ORDER)
        return;

    mIDList[mIDCnt++] = mID;
}

/////////////////////////////////////////////////////////////////////////

#define INIT           		0
#define ADD_COOKIECUTTER    1
#define ORDER_COOKIE  		2
#define CHECK_REMAIN   		3
#define NEW_DAY         	4

static bool run()
{
    int mID;
    int N, mShapeList[MAX_N];
    int mShape, daysLeft;

    int Q;
    int cmd, ret = 0, ans;

    scanf("%d", &Q);

    bool okay = false;

    for (int i = 0; i < Q; ++i)
    {
        scanf("%d", &cmd);
        switch (cmd)
        {
        case INIT:
            init();
            okay = true;
            break;
        case ADD_COOKIECUTTER:
            scanf("%d %d", &mID, &N);
            for (int j = 0; j < N; ++j)
                scanf("%d", &mShapeList[j]);
            if (okay)
                addCookieCutter(mID, N, mShapeList);
            break;
        case ORDER_COOKIE:
            scanf("%d %d", &mShape, &daysLeft);
            if (okay)
                orderCookie(mShape, daysLeft);
            break;
        case CHECK_REMAIN:
            scanf("%d", &mShape);
            if (okay)
                ret = checkRemain(mShape);
            scanf("%d", &ans);
            if (ret != ans)
                okay = false;
            break;
        case NEW_DAY:
            mIDCnt = 0;
            if (okay)
                newDay();
            scanf("%d", &ans);
            if (mIDCnt != ans)
                okay = false;
            for (int k = 0; k < ans; ++k)
            {
                int mID_a;
                scanf("%d", &mID_a);
                if (mIDList[k] != mID_a)
                    okay = false;
            }
            break;
        default:
            okay = false;
        }
    }

    return okay;
}

//int main()
//{
//    setbuf(stdout, NULL);
//    //freopen("sample_input.txt", "r", stdin);
//
//    int T, MARK;
//    scanf("%d %d", &T, &MARK);
//
//    for (int tc = 1; tc <= T; tc++)
//    {
//        int score = run() ? MARK : 0;
//        printf("#%d %d\n", tc, score);
//    }
//
//    return 0;
//}
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

#endif


#if 0
/***********************************************************/
// [쿠키 상점] : 강사님 풀이
/***********************************************************/
#include <list>
#include <queue>

using namespace std;

extern void makeChoco(int moldID);

#define MAX_MOLD                (100)
#define MAX_SHAPE               (1000)
#define MAX_ORDER               (20000)
#define MAX_SHAPE_PER_MOLD      (10)

list<int> mold[MAX_MOLD + 1];

struct ORDER
{
    int seq_order;
    int shape_order;
    int end_time;
    bool flag;

    ORDER* init(int seq_order, int shape_order, int end_time) {
        this->seq_order = seq_order;
        this->shape_order = shape_order;
        this->end_time = end_time;
        this->flag = false;
        return this;
    }
};

ORDER alloc_order[MAX_ORDER];
int alloc_order_idx;

struct COMPP {
    bool operator()(ORDER* a, ORDER* b) {
        if (a->end_time == b->end_time) return a->seq_order > b->seq_order;
        else return a->end_time > b->end_time;
    }
};

priority_queue<ORDER*, vector<ORDER*>, COMPP> pq_order;
priority_queue<ORDER*, vector<ORDER*>, COMPP> pq_shape[MAX_SHAPE + 1];

list<int> moldlist_shape[MAX_SHAPE + 1];

int ct;
int seq_order;

void Init_Mold(void)
{
    int i;
    for (i = 1; i <= MAX_MOLD; i++)
    {
        mold[i].clear();
    }
}

void Init_Shape(void)
{
    int i;
    for (i = 1; i <= MAX_SHAPE; i++)
    {
        moldlist_shape[i].clear();
        pq_shape[i] = priority_queue<ORDER*, vector<ORDER*>, COMPP>();
    }
}

void Init_Order(void)
{
    int i;
    pq_order = priority_queue<ORDER*, vector<ORDER*>, COMPP>();
    alloc_order_idx = 0;
}

void initUser()
{
    ct = 0;
    seq_order = 0;
    Init_Mold();
    Init_Shape();
    Init_Order();
}

void addChocoMold(int moldID, int shapeN, int shapeIDList[])
{
    for (int i = 0; i < shapeN; i++)
    {
        mold[moldID].push_back(shapeIDList[i]);
        moldlist_shape[shapeIDList[i]].push_back(moldID);
    }
}

void orderChoco(int shapeID, int tickLater)
{
    ORDER* order;
    int end_time = ct + tickLater;
    order = alloc_order[alloc_order_idx++].init(seq_order++, shapeID, end_time);

    pq_order.push(order);
    pq_shape[shapeID].push(order);
}

int howRemainShapeID(int shapeID)
{
    return pq_shape[shapeID].size();
}

int Select_Mold(int shape_id)
{
    int cnt;
    int mold_id;
    int max_mold_id = 0x7fffffff, max_cnt = -1;


    for (auto it = moldlist_shape[shape_id].begin(); it != moldlist_shape[shape_id].end(); it++)
    {
        mold_id = *it;
        cnt = 0;
        for (auto iit = mold[mold_id].begin(); iit != mold[mold_id].end(); iit++)
        {
            if (pq_shape[*iit].size() > 0) cnt++;
        }

        if ((cnt > max_cnt) || ((cnt == max_cnt) && (max_mold_id > mold_id)))
        {
            max_cnt = cnt; max_mold_id = mold_id;
        }
    }
    return max_mold_id;
}

void newTick()
{
    int mold_id;
    ORDER* order;

    ORDER* workorder;
    int shape_id;
    ct++;
    while (!pq_order.empty() && pq_order.top()->end_time == ct)
    {
        order = pq_order.top();
        pq_order.pop();

        if (order->flag) continue;

        mold_id = Select_Mold(order->shape_order);

        makeChoco(mold_id);
        for (auto it = mold[mold_id].begin(); it != mold[mold_id].end(); it++)
        {
            shape_id = *it;
            if (!pq_shape[shape_id].empty())
            {
                workorder = pq_shape[shape_id].top();
                pq_shape[shape_id].pop();

                workorder->flag = 1;
            }
        }
    }
}
#endif