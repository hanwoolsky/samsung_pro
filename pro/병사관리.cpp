#include <list>
  
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
DATA hmap[100001];
  
void init(){
    for (int i = 1; i <= 100000; i++) {
        hmap[i].isfire = true;
    }
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            soldScore[i][j].clear();
        }
    }
}
  
void hire(int mID, int mTeam, int mScore){
    hmap[mID].teamNum = mTeam;
    hmap[mID].isfire = 0;
    soldScore[mTeam][mScore].push_back({ mID, ++hmap[mID].seqNum });
}
  
void fire(int mID){
    hmap[mID].isfire = 1;
}
  
void updateSoldier(int mID, int mScore){
    soldScore[hmap[mID].teamNum][mScore].push_back({ mID, ++hmap[mID].seqNum });
}
  
void updateTeam(int mTeam, int mChangeScore){
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
  
int bestSoldier(int mTeam){
    int i = 5;
    int maxScore = 0;
    int id = 0;
    int flag = 0;
    for(int i = 5; i > 0; i--){
        if (soldScore[mTeam][i].size()) {
            for (auto it = soldScore[mTeam][i].begin(); it != soldScore[mTeam][i].end();) {
                if (it->seqNum != hmap[it->idNum].seqNum) it = soldScore[mTeam][i].erase(it);
                else if (hmap[it->idNum].isfire) it = soldScore[mTeam][i].erase(it);
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