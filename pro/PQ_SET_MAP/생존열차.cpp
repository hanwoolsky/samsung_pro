#include <vector>
#include <set>

#define MAX_NUM 100000
#define MAX_JOB 1000

using namespace std;

int userPoint[MAX_NUM + 1];
int iterArr[MAX_NUM + 1];

using pii = pair<int, int>;
set<pii> train[11];
set<pii>::iterator iter[MAX_NUM + 1];

vector<int> joblist[MAX_JOB + 1];

int room;

void init(int N, int M, int J, int mPoint[], int mJobID[]) {
    room = N / M;

    for (int i = 0; i < J; i++) joblist[i].clear();
    for (int i = 0; i < room; i++) train[i].clear();
    for (int i = 0; i < N; i++) {
        userPoint[i] = mPoint[i];
        joblist[mJobID[i]].push_back(i);
        iterArr[i] = i / M; // 위치가 바뀌기 때문에 몇번 칸에 속하는지 배열을 만들어 업데이트 해주어야 한다.
        iter[i] = train[i / M].insert({ -mPoint[i], i }).first;
    }
}

void destroy() {}

int update(int mID, int mPoint) {
    userPoint[mID] += mPoint;

    // set 안의 point 정보도 바꿔주어야함
    train[iterArr[mID]].erase(iter[mID]);
    iter[mID] = train[iterArr[mID]].insert({ -userPoint[mID], mID }).first;

    return userPoint[mID];
}

int updateByJob(int mJobID, int mPoint) {
    int pointSum = 0;
    for (int uid : joblist[mJobID]) {
        userPoint[uid] += mPoint;

        // set 안의 point 정보도 바꿔주어야함
        train[iterArr[uid]].erase(iter[uid]);
        iter[uid] = train[iterArr[uid]].insert({ -userPoint[uid], uid }).first;

        pointSum += userPoint[uid];
    }
    return pointSum;
}

int move(int mNum) {
    vector<int> tmp[11];
    for (int i = 1; i < room; i++) {
        for (int j = 0; j < mNum; j++) {
            tmp[i].push_back(train[i - 1].rbegin()->second); // train[x]의 맨 뒤 pair의 second, 즉 uid를 tmp[x + 1]에 저장 -> 뒤로 넘길 uid
            train[i - 1].erase(--train[i - 1].end()); // train[x]에서 삭제
            tmp[i - 1].push_back(train[i].begin()->second); // train[x]의 맨 앞 pair의 second, 즉 uid를 tmp[x - 1]에 저장 -> 앞으로 넘길 uid
            train[i].erase(train[i].begin()); // train[x]에서 삭제
        }
    }

    int pointSum = 0;
    for (int i = 0; i < room; i++) {
        for (int uid : tmp[i]) {
            iterArr[uid] = i; // i번 칸으로 위치 변경
            iter[uid] = train[i].insert({ -userPoint[uid], uid }).first;
            pointSum += userPoint[uid];
        }
    }

    return pointSum;
}