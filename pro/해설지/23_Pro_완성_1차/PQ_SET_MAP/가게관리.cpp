#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_map>

using namespace std;
using pii = pair<int, int>;
const int PLM = 605;
const int BLM = 30005;
int prodSum[PLM]; // 상품번호별 재고수
struct Product{
    int Bid, Pid, price, num, snum; // 구입 수, 재고 수
    int cancel(int pid){
        if(num!= snum) return -1;
        prodSum[pid] -= num, snum = 0;
        return prodSum[pid];
    }
} prod[BLM];

struct Comp {
    bool operator()(const int a, const int b) const{
        if(prod[a].price != prod[b].price) return prod[a].price > prod[b].price;
        return prod[a].Bid > prod[b].Bid;
    }
};

priority_queue<int, vector<int>, Comp> pq[PLM];
unordered_map<int, int> bHash, pHash;
int bCnt, pCnt;
unordered_map<int, vector<pii>> sTab;

void init(){
    for(int i = 0; i < PLM; ++i) pq[i] = {}, prodSum[i] = 0;
    bCnt = pCnt = 0;
    bHash.clear(), pHash.clear(), sTab.clear();
}

int buy(int BID, int product, int price, int quantity){
    int bid = bHash.count(BID) ? bHash[BID] : bHash[BID] = ++bCnt;
    int pid = pHash.count(product) ? pHash[product] : pHash[product] = ++pCnt;
    prod[bid] = {BID, product, price, quantity, quantity};
    pq[pid].push(bid); // bid만 넣어서 prod[bid]의 price와 BID로 정렬
    prodSum[pid] += quantity;
}

int cancel(int BID){
    if(bHash.count(BID) == 0) return -1; // 구매한 적이 없음
    int bid = bHash[BID];
    int pid = pHash[prod[bid].Pid];
    return prod[bid].cancel(pid);
}

int sell(int SID, int product, int price, int quantity){
    if(pHash.count(product) == 0) return -1; // product 상품을 구매한 적이 없음
    int pid = pHash[product];
    if(prodSum[pid] < quantity) return -1;

    int res = 0;
    while(!pq[pid].empty() && quantity){
        int bid = pq[pid].top();
        if(prod[bid].snum == 0) { // 재고가 없음
            pq[pid].pop();
            continue;
        }
        int minNum = min(prod[bid].snum, quantity); // 판매 가능 개수
        prod[bid].snum -= minNum;
        quantity -= minNum;
        prodSum[pid] -= minNum;
        res += (price - prod[bid].price) * minNum;
        sTab[SID].push_back({bid, minNum});
    }
    return res;
}

int refund(int SID){
    if(sTab.count(SID) == 0) return -1; // 판매한 적이 없거나 이미 환불

    int res = 0;
    for(auto&p:sTab[SID]){
        int bid = p.first, snum = p.second;
        int pid = pHash[prod[bid].Pid];
        if(prod[bid].snum == 0) pq[pid].push(bid); // 재고가 0이면 pop 되었을테니 push
        prod[bid].snum += snum;
        res += snum;
        prodSum[pid] += snum;
    }
    sTab.erase(SID);
    return res;
}