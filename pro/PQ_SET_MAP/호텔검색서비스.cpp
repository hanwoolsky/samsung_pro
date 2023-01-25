// 시간 초과
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#define MAX_HOTEL 1000
#define MAX_ROOM 100000

using namespace std;
using pii = pair<int, int>;

struct hotelInfo {
    int hotelID;
    int roomID;
    int price;
    string condition;
    set<pii> checkout;

    void init() {
        hotelID = 0;
        roomID = 0;
        price = 0;
        condition = "";
        checkout.clear();
    }

    hotelInfo* add(int hotelID, int roomID, int price, string condition) {
        this->hotelID = hotelID;
        this->roomID = roomID;
        this->price = price;
        this->condition = condition;
        return this;
    }
};

int idx;
int roomCnt[MAX_HOTEL + 1];
hotelInfo HOTEL[MAX_ROOM + 1]; // 전체 호텔 정보를 저장하는 배열
vector<hotelInfo*> roomByHotel[MAX_HOTEL + 1]; // 호텔 ID 별 정보 (for 가격 수정)
unordered_map<string, vector<hotelInfo*>> hmap; // 검색 조건에 따른 정보

void init(int N, int mRoomCnt[]){
    idx = 0;
    hmap.clear();
    for (int i = 0; i < MAX_HOTEL; i++) {
        HOTEL[i].init();
        roomCnt[i] = 0;
        roomByHotel[i].clear();
    }
    for (int i = 0; i < N; i++) roomCnt[i + 1] = mRoomCnt[i];
}

string searchCond(int region, int bedCnt, int roomType, int sceneType) {
    string str = "";

    if (region == 10) str += 'a';
    else str += region + '0';

    if (bedCnt == 10) str += 'a';
    else str += bedCnt + '0';

    str += roomType + '0';
    str += sceneType + '0';

    return str;
}

void addRoom(int mHotelID, int mRoomID, int mRoomInfo[]){
    string search = searchCond(mRoomInfo[0], mRoomInfo[1], mRoomInfo[2], mRoomInfo[3]);
    
    hotelInfo* photel = HOTEL[idx++].add(mHotelID, mRoomID, mRoomInfo[4], search);
    roomByHotel[mHotelID].push_back(photel);
    hmap[search].push_back(photel);
}

bool check(set<pii> checkvec, int checkIn, int checkOut) { // 체크인 가능하면 1, 불가능 하면 0 return
    auto it = checkvec.lower_bound({ checkIn, checkOut });
    if (it != checkvec.begin() && checkIn < prev(it, 1)->second) return 0;
    if (it != checkvec.end() && it->first < checkOut) return 0;
    return 1;
}

int findRoom(int mFilter[]){ // 체크인 ~ 체크아웃 기간이 아니면 예약 가능하다. time flow 문제가 아니므로 체크인 날짜가 커질 것이라는 보장 불가
    string search = searchCond(mFilter[2], mFilter[3], mFilter[4], mFilter[5]);
    auto it = hmap.find(search);
    if (it == hmap.end()) return -1;

    bool flag = 0;
    int price = 1000000000;
    int idx = 0;
    int id = 0;
    for (int i = 0; i < it->second.size(); i++) {
        if (!check(it->second[i]->checkout, mFilter[0], mFilter[1])) continue;
        if (it->second[i]->price < price) {
            flag = 1;
            price = it->second[i]->price;
            id = it->second[i]->roomID;
            idx = i;
        }
        else if (it->second[i]->price == price) {
            if (it->second[i]->roomID < id) {
                id = it->second[i]->roomID;
                idx = i;
            }
        }
    }
    if(flag) it->second[idx]->checkout.insert(make_pair(mFilter[0], mFilter[1]));

    return flag ? it->second[idx]->roomID : -1;
}

int riseCosts(int mHotelID){
    int priceSum = 0;
    for (int i = 0; i < roomCnt[mHotelID]; i++) {
        roomByHotel[mHotelID][i]->price += roomByHotel[mHotelID][i]->price / 10;
        priceSum += roomByHotel[mHotelID][i]->price;
    }

    return priceSum;
}


// SET : 456ms
#include <set>
#include <vector>

using namespace std;

using pii = pair<int, int>;

const int MAX_ROOM = 100000;
const int MAX_HOTEL = 1000;
int N;
vector<int> idsByHotel[MAX_HOTEL + 1];
set<pii> ids[11][11][5][5]; // <cost, id>'s asceding

struct Data {
    int region, bedCnt, roomType, viewType, cost, id;
    set<pii>::iterator it; // ids[region][bedCnt][roomType][viewType]에 삽입된 위치
    set<pii> reserveList; // 예약 목록

    void init(int* info, int nid) {
        region = info[0], bedCnt = info[1], roomType = info[2];
        viewType = info[3], cost = info[4], id = nid;
        reserveList.clear();
        // 분류별로 우선순위에 맞게 삽입 : 삽입위치 저장
        it = ids[region][bedCnt][roomType][viewType].insert({ cost, id }).first;
    }

    int updateCost() {
        // 1. 먼저 지우고
        ids[region][bedCnt][roomType][viewType].erase(it);
        // 2. 비용 업데이트 하고
        cost += cost / 10;
        // 3. 다시 삽입하기
        it = ids[region][bedCnt][roomType][viewType].insert({ cost, id }).first;
        return cost;
    }

    int reserve(int inTime, int outTime) {
        auto it = reserveList.lower_bound({ inTime, 0 });
        if (it != reserveList.begin() && inTime < prev(it, 1)->second) return -1;
        if (it != reserveList.end() && it->first < outTime) return -1;
        reserveList.insert({ inTime, outTime });
        return id;
    }
} rooms[MAX_ROOM + 1];

void init(int N, int bedCnt[]) {
    ::N = N;
    for (int i = 1; i <= MAX_HOTEL; ++i) idsByHotel[i].clear(); // 호텔별 방목록 초기화
    // dis[지역][방갯수][방유형][조망유형] 셋 초기화
    for (int i = 1; i < 11; ++i) for (int j = 2; j < 11; ++j) {
        for (int r = 1; r < 5; ++r) for (int c = 1; c < 5; ++c)
            ids[i][j][r][c].clear();
    }
}

void addRoom(int hotelID, int roomID, int roomInfo[]) {
    idsByHotel[hotelID].push_back(roomID); // 호텔별 방번호 추가
    rooms[roomID].init(roomInfo, roomID); // 방정보 저장, 분류별 우선순위에 맞게 저장
}

int findRoom(int filter[]) {
    int re = filter[2], be = filter[3], rt = filter[4], vt = filter[5];
    for (auto pa : ids[re][be][rt][vt]) { // 분류별, 우선순위에 따라 일정에 맞는 방 찾기
        if (rooms[pa.second].reserve(filter[0], filter[1]) > 0)
            return pa.second;
    }
    return -1;
}
int riseCosts(int hotelID) { // hotelID 소속의 방 대여료 인상시키기
    int sum = 0;
    for (int id : idsByHotel[hotelID]) {
        sum += rooms[id].updateCost();
    }
    return sum;
}