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