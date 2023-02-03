#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

void init(int R, int C);
int dropBlocks(int mTimestamp, int mCol, int mLen);
int removeBlocks(int mTimestamp);

#define CMD_INIT 100
#define CMD_DROP 200
#define CMD_REMOVE 300

static bool run()
{
    int query_num;
    scanf("%d", &query_num);

    int ret, ans;
    bool ok = false;

    for (int q = 0; q < query_num; q++)
    {
        int query;
        scanf("%d", &query);

        if (query == CMD_INIT)
        {
            int R, C;
            scanf("%d %d", &R, &C);
            init(R, C);
            ok = true;
        }
        else if (query == CMD_DROP)
        {
            int mTimestamp, mCol, mLen;
            scanf("%d %d %d", &mTimestamp, &mCol, &mLen);
            ret = dropBlocks(mTimestamp, mCol, mLen);
            scanf("%d", &ans);
            if (ans != ret)
            {
                ok = false;
            }
        }
        else if (query == CMD_REMOVE)
        {
            int mTimestamp;
            scanf("%d", &mTimestamp);
            ret = removeBlocks(mTimestamp);
            scanf("%d", &ans);
            if (ans != ret)
            {
                ok = false;
            }
        }

    }
    return ok;
}

int main()
{
    setbuf(stdout, NULL);
    // freopen("sample_input.txt", "r", stdin);
    int T, MARK;
    scanf("%d %d", &T, &MARK);

    for (int tc = 1; tc <= T; tc++)
    {
        int score = run() ? MARK : 0;
        printf("#%d %d\n", tc, score);
    }
    return 0;
}

using namespace std;
#include <cstring>
#include <set>

struct DATA {
    int timestamp;
    int col;
    int length;
    bool operator<(const DATA& t) const {
        return timestamp != t.timestamp ? timestamp < t.timestamp : col < t.col;
    }
};

set<DATA> board; // timestamp 작은 순, col 작은 순 

const int LM = 10001;
int underBlock[LM];
int row, column;
int blocks;

void curStatus(int curTime) {
    for (auto it = board.begin(); it != board.end();) {
        if (curTime - it->timestamp + 1 > row) {
            blocks -= it->length;
            it = board.erase(it);
        }
        else break;
    }
}

void init(int R, int C){
    row = R, column = C;
    blocks = 0;
    board.clear();
}

int dropBlocks(int mTimestamp, int mCol, int mLen)
{
    curStatus(mTimestamp);

    board.insert({mTimestamp, mCol, mLen});
    blocks += mLen;

    return blocks;
}

int removeBlocks(int mTimestamp)
{
    curStatus(mTimestamp);
    memset(underBlock, 0, LM * sizeof(int));

    int times, start, end, s, e, i;
    int removeBlock = 0;
    for (auto it = board.begin(); it != board.end();) {
        times = it->timestamp; start = it->col; end = it->col + it->length;
        it = board.erase(it);
        s = start; e = end;
        for (i = start; i < end - 1; i++){
            if (underBlock[i] != underBlock[i + 1]) {
                if (underBlock[i] == 0) {
                    s = i + 1;
                    underBlock[i] = 1;
                    removeBlock++;
                }
                else {
                    e = i + 1;
                    board.insert({ times, s, e - s });
                }
            }
            else {
                if (underBlock[i] == 0) {
                    underBlock[i] = 1;
                    removeBlock++;
                }
            }
        }
        if (underBlock[i] == 0) {
            underBlock[i] = 1;
            removeBlock++;
        }
        else {
            e = i + 1;
            board.insert({ times, s, e - s });
        }
    }
    blocks -= removeBlock;

    return blocks;
}
// think 1. it로 돌리면 새로운 데이터를 추가하면서 탐색해야할 데이터가 늘지 않나? => 안 늘어요.


// #[way2] 시간 단축, 생각해야 할 예외 지점 증가
using namespace std;
#include <cstring>
#include <set>

struct DATA {
    int timestamp;
    int col;
    int length;
    bool operator<(const DATA& t) const {
        return timestamp != t.timestamp ? timestamp < t.timestamp : col < t.col;
    }
};

set<DATA> board; // timestamp 작은 순, col 작은 순 

const int LM = 10001;
int underBlock[LM];
int row, column;
int blocks;

void curStatus(int curTime) {
    for (auto it = board.begin(); it != board.end();) {
        if (curTime - it->timestamp + 1 > row) {
            blocks -= it->length;
            it = board.erase(it);
        }
        else break;
    }
}

void init(int R, int C){
    row = R, column = C;
    blocks = 0;
    board.clear();
}

int dropBlocks(int mTimestamp, int mCol, int mLen)
{
    curStatus(mTimestamp);

    board.insert({mTimestamp, mCol, mLen});
    blocks += mLen;

    return blocks;
}

int removeBlocks(int mTimestamp)
{
    curStatus(mTimestamp);
    memset(underBlock, 0, LM * sizeof(int));

    int times, start, end, s, e, i;
    int removeBlock = 0;
    for (auto it = board.begin(); it != board.end();) {
        times = it->timestamp; start = it->col; end = it->col + it->length;
        it = board.erase(it);
        s = start; e = end;
        for (i = start; i < end - 1; i++){
            if (underBlock[i] != underBlock[i + 1]) {
                if (underBlock[i] == 0) {
                    s = i + 1;
                    underBlock[i] = 1;
                    removeBlock++;
                }
                else {
                    e = i + 1;
                    board.insert({ times, s, e - s });
                }
            }
            else {
                if (underBlock[i] == 0) {
                    underBlock[i] = 1;
                    removeBlock++;
                }
            }
        }
        if (underBlock[i] == 0) {
            underBlock[i] = 1;
            removeBlock++;
        }
        else {
            e = i + 1;
            board.insert({ times, s, e - s });
        }
    }
    blocks -= removeBlock;

    return blocks;
}