// 990ms
#include <set>
#include <vector>
#define MAX_N (11001)
 
using namespace std;
 
struct objectInfo {
    int y1, x1, y2, x2;
    vector<int> subObject;
} idObj[MAX_N];
 
set<int> object;
int objSize, cnt;
 
void init(int N){
    object.clear();
    for (int i = 0; i < MAX_N; i++) {
        idObj[i].subObject.clear();
    }
    objSize = N;
    cnt = 0;
}
 
void addObject(int mID, int y1, int x1, int y2, int x2){
    idObj[mID].y1 = y1;
    idObj[mID].x1 = x1;
    idObj[mID].y2 = y2;
    idObj[mID].x2 = x2;
    object.insert(object.end(), mID);
}
 
bool checkInside(int mID, int y1, int x1, int y2, int x2) {
    if (y1 <= idObj[mID].y1 && idObj[mID].y1 <= y2 && y1 <= idObj[mID].y2 && idObj[mID].y2 <= y2 && x1 <= idObj[mID].x1 && idObj[mID].x1 <= x2 && x1 <= idObj[mID].x2 && idObj[mID].x2 <= x2) return 1;
    return 0;
}
 
int group(int mID, int y1, int x1, int y2, int x2){
    int final_y1 = objSize + 1, final_x1 = objSize + 1, final_y2 = 0, final_x2 = 0;
    int sum = 0;
    for (auto it = object.begin(); it != object.end();) {
        if (checkInside(*it, y1, x1, y2, x2)) { // 영역 안에 포함되면
            //printf("%d %d\n", mID, *it);
            idObj[mID].subObject.push_back(*it);
            sum += *it;
            if (final_y1 > idObj[*it].y1) final_y1 = idObj[*it].y1;
            if (final_y2 < idObj[*it].y2) final_y2 = idObj[*it].y2;
            if (final_x1 > idObj[*it].x1) final_x1 = idObj[*it].x1;
            if (final_x2 < idObj[*it].x2) final_x2 = idObj[*it].x2;
            it = object.erase(it);
        }
        else {
            it++;
        }
    }
    if (idObj[mID].subObject.size() > 1) {
        object.insert(mID);
        idObj[mID].y1 = final_y1;
        idObj[mID].x1 = final_x1;
        idObj[mID].y2 = final_y2;
        idObj[mID].x2 = final_x2;
    }
    else {
        for (int i = 0; i < idObj[mID].subObject.size(); i++) {
            object.insert(idObj[mID].subObject[i]);
        }
        idObj[mID].subObject.clear();
        sum = 0;
    }
 
    return sum;
}
 
int countChild(int mID) {
    if (idObj[mID].subObject.size() == 0) cnt += 1;
    for (int i = 0; i < idObj[mID].subObject.size(); i++) {
        if (idObj[idObj[mID].subObject[i]].subObject.size() == 0) { // 개인 개체
            cnt += 1;
            object.insert(idObj[mID].subObject[i]);
        }
        else {
            countChild(idObj[mID].subObject[i]);
            object.erase(idObj[mID].subObject[i]);
        }
    }
    return cnt;
}
 
void updateChild(int mID, int delx, int dely){
    if (idObj[mID].subObject.size() == 0) {
        idObj[mID].y1 += dely;
        idObj[mID].y2 += dely;
        idObj[mID].x1 += delx;
        idObj[mID].x2 += delx;
    }
    else {
        for (int vvi = 0; vvi < idObj[mID].subObject.size(); vvi++) {
            updateChild(idObj[mID].subObject[vvi], delx, dely);
        }
    }
}
 
int ungroup(int y1, int x1){
    cnt = 0;
    for (auto it = object.rbegin(); it != object.rend(); it++) {
        if (idObj[*it].y1 <= y1 && y1 <= idObj[*it].y2 && idObj[*it].x1 <= x1 && x1 <= idObj[*it].x2) { // *it(mID)가 (y1, x1)을 포함
            cnt = countChild(*it);
            if(cnt != 1) object.erase(*it);
            break;
        }
    }
 
    return cnt;
}
 
int moveObject(int y1, int x1, int y2, int x2){
    int ans = -1;
    for (auto it = object.rbegin(); it != object.rend(); it++) {
        if (idObj[*it].y1 <= y1 && y1 <= idObj[*it].y2 && idObj[*it].x1 <= x1 && x1 <= idObj[*it].x2) { // *it(mID)가 (y1, x1)을 포함
            int dely = y2 - idObj[*it].y1;
            int delx = x2 - idObj[*it].x1;
            if (idObj[*it].y2 + dely > objSize - 1) dely -= (idObj[*it].y2 + dely - objSize + 1);
            if (idObj[*it].x2 + delx > objSize - 1) delx -= (idObj[*it].x2 + delx - objSize + 1);
 
            idObj[*it].y1 += dely;
            idObj[*it].y2 += dely;
            idObj[*it].x1 += delx;
            idObj[*it].x2 += delx;
 
            ans = idObj[*it].y1 * 10000 + idObj[*it].x1;
 
            for (int vi = 0; vi < idObj[*it].subObject.size(); vi++) {
                updateChild(idObj[*it].subObject[vi], delx, dely);
            }
            break;
        }
    }
 
    return ans;
}

// 270ms
#define MAX_DATA_WH 9

#include<vector>
using namespace std;

int N, M;   // 좌표 범위, 개체 수

struct Object {
    bool active;                // 개체가 유효한지 판별
    int x1, y1, x2, y2;         // 개체의 구간
    vector<int> v;              // 개체에 포함된 단일개체 번호

    void move(int dx, int dy) { // 개체의 구간 += (dx, dy)
        x1 += dx, x2 += dx;
        y1 += dy, y2 += dy;
    }
}O[11003];

void init(int N) {
    ::N = N;
    M = 0;
}

void addObject(int mID, int x1, int y1, int x2, int y2)
{
    M++;
    O[mID] = { 1, x1, y1, x2, y2, {mID} };
}

int group(int mID, int x1, int y1, int x2, int y2)
{
    // 개수 증가, 개체 초기화
    M++;
    auto&o = O[mID] = { 0, N, N, 0, 0, {} };

    // 범위에 포함되는 개체를 tmp에 기록
    vector<int> tmp;
    for (int i = 1; i < M; i++) {
        if (O[i].active == 0) continue;
        if (x1 <= O[i].x1 && O[i].x2 <= x2 && y1 <= O[i].y1 && O[i].y2 <= y2)
            tmp.push_back(i);
    }
    if (tmp.size() < 2) return 0;

    // 포함되는 개체가 2개 이상인 경우 그룹 개체 생성
    o.active = 1;
    int sum = 0;
    for (int c : tmp) {
        o.x1 = min(o.x1, O[c].x1);
        o.x2 = max(o.x2, O[c].x2);
        o.y1 = min(o.y1, O[c].y1);
        o.y2 = max(o.y2, O[c].y2);
        o.v.insert(o.v.end(), O[c].v.begin(), O[c].v.end());

        O[c].active = 0;
        sum += c;
    }
    return sum;

}

// (x1, y1)에 속한 개체 중 가장 큰 번호 반환
int getID(int x1, int y1) {
    for (int i = M; i >= 1; i--) {
        if (O[i].active == 0) continue;
        if (O[i].x1 <= x1 && x1 <= O[i].x2 && O[i].y1 <= y1 && y1 <= O[i].y2)
            return i;
    }
    return 0;
}

int ungroup(int x1, int y1)
{
    int id = getID(x1, y1);
    if (id == 0) return 0;

    // 개체 해제, 포함된 모든 단일개체 활성화 (단일개체 였던 경우도 문제 없음)
    O[id].active = 0;
    for (int c : O[id].v)
        O[c].active = 1;
    return O[id].v.size();
}

int moveObject(int x1, int y1, int x2, int y2)
{
    int id = getID(x1, y1);
    if (id == 0) return -1;

    int dx = min(x2 - O[id].x1, N - 1 - O[id].x2);  // x변화량
    int dy = min(y2 - O[id].y1, N - 1 - O[id].y2);  // y변화량

    O[id].move(dx, dy);             // id 개체 좌표 이동

    if (O[id].v.size() > 1)         // 그룹 해제 됐을때를 위해 id가 그룹 개체일때만
        for (int c : O[id].v)       // 포함된 모든 단일개체도 이동
            O[c].move(dx, dy);

    return O[id].x1*10000 + O[id].y1;
}