// 강사님 풀이
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