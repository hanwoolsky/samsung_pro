#include<unordered_map>
#include<string>
#include<string.h>
#include<algorithm>
using namespace std;

int n, m;
struct Data { int uid, x, y; };
unordered_map<string, vector<Data>> S;  // S[word] = word 포함된 정보 리스트

string B[1003][13][13];         // 빙고판, 지워지면 ""
struct Cnt {
    int x[10], y[10], lt, rt;   // x[i] : i줄 삭제 개수 , y[j] : j열 삭제 개수, lt : 좌상 대각 , rt : 우상 대각
}C[1003];
int curRound;   // 현재 라운드
int done;       // 종료시, 승자의 완성빙고 개수

void init(int N, int M) {
    curRound = done = 0;
    S.clear();
    n = N, m = M;
    memset(C, 0, sizeof(C));
}

void registerUser(int uid, char board[10][10][11]) {
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
        B[uid][i][j] = board[i][j];
        S[board[i][j]].push_back({ uid, i,j });
    }
}

struct Select {
    int cnt, diag, x, y;
    bool operator<(Select&r) {
        if (cnt != r.cnt) return cnt < r.cnt;
        if (diag != r.diag) return diag < r.diag;
        if (x != r.x) return x > r.x;
        return y > r.y;
    }
};

string select(int uid) {
    Select ret = { -1 };
    auto&b = B[uid];
    auto&c = C[uid];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (b[i][j] == "") continue;

            int cnt = max(c.x[i], c.y[j]), diag = 0;
            if (i == j) cnt = max(cnt, c.lt), diag++;
            if (i + j == n - 1) cnt = max(cnt, c.rt), diag++;

            Select now = { cnt, diag, i, j };
            if (ret < now) ret = now;
        }
    }
    return b[ret.x][ret.y];
}

void erase(string str) {
    for (Data&d : S[str]) {
        int uid = d.uid, x = d.x, y = d.y;
        B[uid][x][y] = "";
        C[uid].x[x]++;
        C[uid].y[y]++;
        if (x == y) C[uid].lt++;
        if (x + y == n - 1) C[uid].rt++;
        done = max(done, (C[uid].x[x] == n) + (C[uid].y[y] == n) + (C[uid].lt == n) + (C[uid].rt == n));
    }
}

string next() {
    int uid = (curRound++ % m) + 1;
    string str = select(uid);
    erase(str);
    return str;
}

void selectWord(int round, char word[]) {
    string ret;
    while (curRound < round) ret = next();
    strcpy(word, ret.c_str());
}

bool isWinner(Cnt&c) {
    int cnt = (c.lt == n) + (c.rt == n);
    for (int i = 0; i < n; i++) cnt += (c.x[i] == n) + (c.y[i] == n);
    return cnt == done;
}

int getResult()
{
    while (!done) next();

    int ret = 0;
    for (int i = 1; i <= m; i++) ret += i * isWinner(C[i]);
    return ret;
}