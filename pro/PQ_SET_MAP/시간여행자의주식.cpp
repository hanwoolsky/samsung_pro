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
    return mQuantity;
}

void cancel(int mNumber){
    cancled[mNumber] = 1;
}

int bestProfit(int mStock){
    return stockBid[mStock].max_benefit;
}