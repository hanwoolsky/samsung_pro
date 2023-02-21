#include <set>
using namespace std;

struct DATA {
    int hori;
    int direct; // -1 왼쪽, 1 오른쪽
    bool operator<(const DATA& t) const {
        return hori < t.hori;
    }
};

set<DATA> ladder[101];

void init(){
    for (int i = 0; i < 101; i++) ladder[i].clear();
}

void add(int mX, int mY){
    ladder[mX].insert({ mY, 1 });
    ladder[mX + 1].insert({ mY, -1 });
}

void remove(int mX, int mY){
    ladder[mX].erase({ mY, 1 });
    ladder[mX + 1].erase({ mY, 0 });
}

int getCrossCnt(int lineID){
    int x = lineID;
    int y = 0;
    int cnt = 0;
    while (y < 1000000000) {
        if (ladder[x].size()) {
            auto it = ladder[x].lower_bound({ y, 0 });
            if (it == ladder[x].end()) y = 1000000000;
            else if (y != it->hori) {
                y = it->hori;
                x += it->direct;
                cnt++;
            }
            else if(y == it->hori && next(it, 1) != ladder[x].end()){
                y = next(it, 1)->hori;
                x += next(it, 1)->direct;
                cnt++;
            }
            else y = 1000000000;
        }
        else y = 1000000000;
    }
    return cnt;
}

int getLineID(int mX, int mY) {
    int x = mX;
    int y = mY;
    while (y) {
        if (ladder[x].size()) {
            auto it = ladder[x].lower_bound({ y, 0 });
            if (it == ladder[x].end() || it != ladder[x].begin()) {
                y = prev(it, 1)->hori;
                x += prev(it, 1)->direct;
            }
            else y = 0;
        }
        else y = 0;
    }
    return x;
}