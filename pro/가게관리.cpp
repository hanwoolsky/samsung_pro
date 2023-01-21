#include <queue>
#include <unordered_map>
#include <list>
#define MAX_PROD (30000)
#define MAX_NUM (600)

using namespace std;

struct DATA {
    int bId;
    int prodId;
    int price;
    int quant;
    bool canceled;
    bool allSold;

    DATA* init(int bId, int prodId, int price, int quant) {
        this->bId = bId;
        this->prodId = prodId;
        this->price = price;
        this->quant = quant;
        this->canceled = false;
        this->allSold = false;
        return this;
    }
};

DATA realMem[MAX_PROD + 1]; // 실제 데이터 저장할 배열
int realMemIdx; // 실제 데이터 저장할 배열의 인덱스
int bIdx; // bID renumbering할 인덱스
int pIdx; // mProduct renumbering할 인덱스
int sIdx; // sID renumbering할 인덱스

struct COMP {
    bool operator()(const DATA* x, const DATA* y) {
        return x->price != y->price ? x->price > y->price : x->bId > y->bId;
    }
};

struct PROD {
    int totalNum;
    priority_queue<DATA*, vector<DATA*>, COMP> prodPQ;

    void init() {
        totalNum = 0;
        prodPQ = {};
    }
};


PROD prod[MAX_NUM + 1]; // mProduct번호에 따른 상품 정보의 포인터와 총 개수를 담는 배열
DATA* BID[MAX_PROD + 1]; // BID에 따른 상품 정보의 포인터를 담는 배열
int bidQuan[MAX_PROD + 1]; // BID의 구매 수량을 저장하는 배열

unordered_map<int, int> bmap;
unordered_map<int, int> pmap;
unordered_map<int, int> smap;

list<DATA> sellPQ[MAX_PROD + 1]; // SID에 따른 판매 목록을 저장하는 배열

void init() {
    realMemIdx = bIdx = pIdx = sIdx = 0;
    for (int i = 0; i <= MAX_PROD; i++) {
        BID[i] = 0;
        bidQuan[i] = 0;
        sellPQ[i].clear();
    }
    for (int i = 0; i <= MAX_NUM; i++) {
        prod[i].init();
    }
    bmap.clear();
    pmap.clear();
    smap.clear(); // 세 map을 clear하지 않아서 한 TC가 segmentation error가 떴다.
}

int getBIdx(int id) {
    auto it = bmap.find(id);
    if (it == bmap.end()) it = bmap.insert({ id, bIdx++ }).first;
    return it->second;
}

int getProdIdx(int id) {
    auto it = pmap.find(id);
    if(it == pmap.end()) it = pmap.insert({id, pIdx++}).first;
    return it->second;
}

int getSIdx(int id) {
    auto it = smap.find(id);
    if(it == smap.end()) it = smap.insert({id, sIdx++}).first; 
    return it->second;
}

int buy(int bId, int mProduct, int mPrice, int mQuantity) {
    DATA* pdata = realMem[realMemIdx++].init(bId, mProduct, mPrice, mQuantity);
    int buyIdx = getBIdx(bId);
    int prodIdx = getProdIdx(mProduct);

    BID[buyIdx] = pdata;
    bidQuan[buyIdx] = mQuantity;
    prod[prodIdx].prodPQ.push(pdata);
    prod[prodIdx].totalNum += mQuantity;

    return prod[prodIdx].totalNum;
}

int cancel(int bId) {
    auto it = bmap.find(bId);
    if (it == bmap.end()) return -1; // bId로 구매한 적이 없음

    int buyIdx = it->second;
    if (BID[buyIdx]->quant != bidQuan[buyIdx] || BID[buyIdx]->canceled) return -1; // 수량이 다르거나 이미 취소함

    BID[buyIdx]->canceled = true; // 취소

    int prodIdx = getProdIdx(BID[buyIdx]->prodId);
    prod[prodIdx].totalNum -= BID[buyIdx]->quant; // mProduct의 총 수량을 조정
    return prod[prodIdx].totalNum;
}

int sell(int sId, int mProduct, int mPrice, int mQuantity) {
    int prodIdx = getProdIdx(mProduct);
    if (prod[prodIdx].totalNum < mQuantity) return -1; // 재고가 부족

    int sellIdx = getSIdx(sId);
    int revenue = 0;
    while (!prod[prodIdx].prodPQ.empty() && mQuantity) {
        if (prod[prodIdx].prodPQ.top()->canceled) {
            prod[prodIdx].prodPQ.pop(); // 취소된 상품이면 제거
            continue;
        }

        DATA* pdata = prod[prodIdx].prodPQ.top();
        if (pdata->quant < mQuantity) {
            revenue += (mPrice - pdata->price) * pdata->quant;
            mQuantity -= pdata->quant;
            prod[prodIdx].totalNum -= pdata->quant;
            pdata->allSold = true;
            sellPQ[sellIdx].push_back({pdata->bId, pdata->prodId, pdata->price, pdata->quant, pdata->canceled, pdata->allSold});
            pdata->quant = 0;
            prod[prodIdx].prodPQ.pop();
        }
        else {
            revenue += (mPrice - pdata->price) * mQuantity;
            pdata->quant -= mQuantity;
            prod[prodIdx].totalNum -= mQuantity;
            sellPQ[sellIdx].push_back({ pdata->bId, pdata->prodId, pdata->price, mQuantity, pdata->canceled, pdata->allSold });
            mQuantity = 0;
        }
    }

    return revenue;
}

int refund(int sId) {
    auto it = smap.find(sId);
    if (it == smap.end()) return -1; // sId로 판매한 내역이 없음

    int sellIdx = it->second;
    if (sellPQ[sellIdx].size() == 0) return -1; // 이미 환불해줌

    int totalRefund = 0;
    for(auto it = sellPQ[sellIdx].begin(); it != sellPQ[sellIdx].end(); it++) {
        DATA data = *it;
        int buyIdx = getBIdx(data.bId);
        int prodIdx = getProdIdx(data.prodId);

        DATA* pdata = BID[buyIdx];
        if (pdata->allSold) {
            pdata->allSold = false;
            pdata->quant += data.quant;
            prod[prodIdx].prodPQ.push(pdata);
        }
        else pdata->quant += data.quant;

        prod[prodIdx].totalNum += data.quant;
        totalRefund += data.quant;
    }
    sellPQ[sellIdx].clear();

    return totalRefund;
}