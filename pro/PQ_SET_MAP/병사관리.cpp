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

// 다시 풀어본 것 390ms
#include <list>
#define MAX_NUM 100000
#define MAX_TEAM 5
#define MAX_SCORE 5

using namespace std;

struct SOLDIER {
    int teamID;
    int seqNum;
    bool isFire;
    void init(int teamID) {
        this->teamID = teamID;
        this->seqNum = 0;
        this->isFire = false;
    }
};

struct SOLDINTEAM {
    int soldID;
    int seq;
};

struct TEAM {
    list<SOLDINTEAM> list_score[MAX_SCORE + 1];
    void init() {
        for (int i = 1; i <= MAX_SCORE; i++) list_score[i].clear();
    }
};

SOLDIER soldier[MAX_NUM + 1];
TEAM teams[MAX_TEAM + 1];

void init(){
    for (int i = 1; i <= MAX_TEAM; i++) teams[i].init();
}

void hire(int mID, int mTeam, int mScore){
    soldier[mID].init(mTeam); // 병사 정보 입력
    teams[mTeam].list_score[mScore].push_back({ mID, soldier[mID].seqNum });
}

void fire(int mID){
    soldier[mID].isFire = true;
}

void updateSoldier(int mID, int mScore){
    teams[soldier[mID].teamID].list_score[mScore].push_back({ mID, ++soldier[mID].seqNum });
}

void updateTeam(int mTeam, int mChangeScore){
    if (mChangeScore > 0) {
        for (int i = 4; i > 0; i--) {
            int score = i + mChangeScore;
            if (i + mChangeScore > 5) score = 5;
            auto it = teams[mTeam].list_score[score].begin();
            teams[mTeam].list_score[score].splice(it, teams[mTeam].list_score[i]);
        }
    }
    else if (mChangeScore < 0) {
        for (int i = 2; i < 6; i++) {
            int score = i + mChangeScore;
            if (i + mChangeScore < 1) score = 1;
            auto it = teams[mTeam].list_score[score].begin();
            teams[mTeam].list_score[score].splice(it, teams[mTeam].list_score[i]);
        }
    }
}

int bestSoldier(int mTeam){
    int id = 0;
    bool flag = 0;
    for (int i = 5; i > 0; i--) {
        if (teams[mTeam].list_score[i].size()) {
            for (auto it = teams[mTeam].list_score[i].begin(); it != teams[mTeam].list_score[i].end();) {
                if (soldier[it->soldID].isFire) it = teams[mTeam].list_score[i].erase(it);
                else if (soldier[it->soldID].seqNum != it->seq) it = teams[mTeam].list_score[i].erase(it);
                else if (it->soldID > id) {
                    id = it->soldID;
                    flag = 1;
                    it++;
                }
                else it++;
            }
            if (flag) break;
        }
    }
    return id;
}

// 강사님 풀이
#include <list>
 
using namespace std;
 
#define MAX_SCORE (5)
#define MAX_TEAM (5)
#define MAX_ID  (100000)
 
struct LENTRY {
    int id;    int seq;
    LENTRY(int id, int seq) {
        this->id = id; this->seq = seq;
    }
};
 
struct MERCENARY {
    int mTeam;
    bool fired;
    int seq;
};
 
struct TEAM {
    list <LENTRY> list_score[MAX_SCORE + 1];
    void init() {
        for (int i = 0; i <= MAX_SCORE; i++) {
            list_score[i].clear();
        }
    }
};
 
MERCENARY mercenary[MAX_ID + 1];
TEAM teams[MAX_TEAM + 1];
int seqnum = 0;
void init()
{
    for (int i = 1; i <= MAX_ID; i++) {
        mercenary[i].fired = true;
    }
 
    for (int i = 1; i <= MAX_TEAM; i++) {
        teams[i].init();
    }
    seqnum = 0;
}
 
void hireMercenary(int mID, int mTeam, int mScore) {
    mercenary[mID].mTeam = mTeam;
    mercenary[mID].seq = ++seqnum;
    mercenary[mID].fired = false;
    teams[mTeam].list_score[mScore].push_back({ mID, mercenary[mID].seq });
}
 
void fireMercenary(int mID) {
    mercenary[mID].fired = true;
}
 
void updateMercenaryScore(int mID, int mScore)
{
    int mTeam = mercenary[mID].mTeam;
    mercenary[mID].seq = ++seqnum;
    teams[mTeam].list_score[mScore].push_back({ mID, mercenary[mID].seq });
}
 
void updateTeamScore(int mTeam, int mChangeScore)
{
    if (mChangeScore == 0) return;
    if (mChangeScore > 0) {
        for (int i = 4; i >= 1; i--) {
            int target = i + mChangeScore;
            if (target > 5) target = 5;
            teams[mTeam].list_score[target].splice(teams[mTeam].list_score[target].end(), teams[mTeam].list_score[i]);
        }
    }
    else {
        for (int i = 2; i <= 5; i++) {
            int target = i + mChangeScore;
            if (target < 1) target = 1;
            teams[mTeam].list_score[target].splice(teams[mTeam].list_score[target].end(), teams[mTeam].list_score[i]);
        }
    }
}
 
int bestMercenary(int mTeam)
{
    int ret = -1;
    for (int i = 5; i >= 1; i--) {
        auto iter = teams[mTeam].list_score[i].begin();
        while (iter != teams[mTeam].list_score[i].end()) {
            if (!mercenary[(*iter).id].fired && mercenary[(*iter).id].seq == (*iter).seq) {
                if (ret < (*iter).id) ret = (*iter).id;
                iter++;
            }
            else {
                iter = teams[mTeam].list_score[i].erase(iter);
            }
        }
        if (ret != -1) break;
    }
    return ret;
}