#include <list>
#include <queue>
#include <unordered_map>

#define MAX_CAR 70000

using namespace std;

struct carInfo {
    int carID;
    int arriveTime;
    int totalWaitTime;
    int totalParkTime;
    int flag; // 0 : 주차장, 1 : 대기열, 2: 대기열 삭제

    void init(int ci, int at, int twt, int tpt, int flag) {
        this->carID = ci;
        this->arriveTime = at;
        this->totalWaitTime = twt;
        this->totalParkTime = tpt;
        this->flag = flag;
    }
};

struct COMP {
    bool operator()(carInfo& x, carInfo& y) {
        return (x.totalWaitTime - x.arriveTime - x.totalParkTime) != (y.totalWaitTime - y.arriveTime - y.totalParkTime) ? (x.totalWaitTime - x.arriveTime - x.totalParkTime) < (y.totalWaitTime - y.arriveTime - y.totalParkTime) : x.arriveTime > y.arriveTime;
    }
};

unordered_map<int, int> hmap;
list<carInfo> parkingLot; // 주차장
list<carInfo>::iterator iter[MAX_CAR + 1];
priority_queue<carInfo, vector<carInfo>, COMP> waitingLot; // 대기열
carInfo CARINFO[MAX_CAR + 1]; // 자동차 정보

int baseTime, baseFee, unitTime, unitFee, capacity;
int idx; // renumbering idx
int waitingNum;

int getKey(int carId) {
    auto it = hmap.find(carId);
    if (it == hmap.end()) it = hmap.insert({ carId, idx++ }).first;
    return it->second;
}

void init(int mBaseTime, int mBaseFee, int mUnitTime, int mUnitFee, int mCapacity) {
    idx = waitingNum = 0;
    baseTime = mBaseTime;  baseFee = mBaseFee; unitTime = mUnitTime; unitFee = mUnitFee; capacity = mCapacity;
    hmap.clear();
    parkingLot.clear();
    waitingLot = {};
    for (int i = 0; i < MAX_CAR; i++) {
        CARINFO[i].totalWaitTime = CARINFO[i].totalParkTime = 0;
    }
}

int arrive(int mTime, int mCar) {
    int carIdx = getKey(mCar);

    int totalWait = CARINFO[carIdx].totalWaitTime;
    int totalPark = CARINFO[carIdx].totalParkTime;

    if (parkingLot.size() < capacity) { // 주차장 비었음
        CARINFO[carIdx].init(mCar, mTime, totalWait, totalPark, 0);
        iter[carIdx] = parkingLot.insert(parkingLot.begin(), { mCar, mTime, totalWait, totalPark, 0 });
    }
    else { // 주차장 다 찼음
        CARINFO[carIdx].init(mCar, mTime, totalWait, totalPark, 1);
        waitingLot.push({ mCar, mTime, totalWait, totalPark, 1 });
        waitingNum++;
    }
    
    return waitingNum;
}

int calcFee(int mTime) {
    int fee = 0;
    if (mTime <= baseTime) fee = baseFee;
    else {
        if ((mTime - baseTime) % unitTime != 0) fee = baseFee + unitFee * ((mTime - baseTime) / unitTime + 1);
        else fee = baseFee + unitFee * ((mTime - baseTime) / unitTime);
    }
    return fee;
}

int leave(int mTime, int mCar) {
    int carIdx = getKey(mCar);
    int fee = -1;
    if (CARINFO[carIdx].flag == 1) { // 대기열에 있는 자동차
        CARINFO[carIdx].flag = 2;
        CARINFO[carIdx].totalWaitTime += (mTime - CARINFO[carIdx].arriveTime);
        waitingNum--;
    }
    else { // 주차장에 있는 자동차
        int parkingTime = mTime - CARINFO[carIdx].arriveTime;
        fee = calcFee(parkingTime);
        CARINFO[carIdx].totalParkTime += parkingTime;
        parkingLot.erase(iter[carIdx]);

        while (!waitingLot.empty()) { // 대기열에 있는 자동차 추가
            carInfo car = waitingLot.top();
            int newcarIdx = getKey(car.carID);
            if (CARINFO[newcarIdx].flag == 2 || CARINFO[newcarIdx].arriveTime != car.arriveTime) waitingLot.pop(); // pq에서는 pop되지 않은 상태로 새롭게 들어오면 flag가 1로 바뀌어 걸러내지 못한다.
            else {
                waitingLot.pop();
                waitingNum--;
                CARINFO[newcarIdx].flag = 0;
                CARINFO[newcarIdx].totalWaitTime += (mTime - car.arriveTime);
                CARINFO[newcarIdx].arriveTime = mTime;

                iter[newcarIdx] = parkingLot.insert(parkingLot.begin(), { car.carID, mTime, CARINFO[newcarIdx].totalWaitTime, CARINFO[newcarIdx].totalParkTime, 0 });
                break;
            }
        }
    }

    return fee;
}