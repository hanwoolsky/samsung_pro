#include<queue>
#include<vector>
#include<unordered_set>
#include<string.h>
using namespace std;
using pii = pair<int, int>;

int n, gcnt;        // 게임판 크기, 마지막 부여된 구역 번호
int bcnt[203][203]; // 겹쳐진 bar의 개수
int gid[203][203];  // 빈 공간의 구역 번호    
struct Bar {
    int x, y, dir, len;
}bar[1000000];
unordered_set<int> used;  // 사용중인 구역 번호
int dx[] = { -1,1,0,0 }, dy[] = { 0,0,-1,1 };

void init(int N)
{
    n = N;
    gcnt = 0;
    used = { 0 };
    memset(bcnt, 0, sizeof(bcnt));
    memset(gid, 0, sizeof(gid));
    for (int i = 0; i <= n + 1; i++)    // 경계 표시
        bcnt[0][i] = bcnt[n + 1][i] = bcnt[i][0] = bcnt[i][n + 1] = -1;
}

vector<pii> mark;

void bfs(int sx, int sy) {
    used.insert(++gcnt);
    queue<pii> q;
    q.push({ sx,sy });
    gid[sx][sy] = gcnt;

    while (q.size()) {
        pii p = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            int x = p.first + dx[i];
            int y = p.second + dy[i];
            if (bcnt[x][y] != 0 || gid[x][y] == gcnt) continue;
            q.push({ x,y });
            gid[x][y] = gcnt;
        }
    }
}

void proc() {
    int orgMaxGid = gcnt;
    for (pii p : mark) {
        if (gid[p.first][p.second] <= orgMaxGid)
            bfs(p.first, p.second);
    }
}

int add(int bID, int len, int row, int col, int dir)
{
    mark.clear();
    bar[bID] = { row, col, dir, len };

    int x = row, y = col;
    for (int i = 0; i < len; i++) {                     // 막대 추가
        if (bcnt[x][y] == 0) used.erase(gid[x][y]);     // 비어있던 경우, 구역 해제
        bcnt[x][y]++;
        x += dx[dir], y += dy[dir];
    }

    x = row, y = col;
    for (int i = 0; i < len; i++) {                     // 추가된 막대 주변 빈 공간
        for (int j = 0; j < 4; j++) {                   // : mark 추가, 구역 해제
            int nx = x + dx[j], ny = y + dy[j];
            if (bcnt[nx][ny] == 0) {
                used.erase(gid[nx][ny]);
                mark.push_back({ nx,ny });
            }
        }
        x += dx[dir], y += dy[dir];
    }
    proc();
    return used.size();
}

int remove(int bID)
{
    mark.clear();
    int x = bar[bID].x, y = bar[bID].y;
    for (int i = 0; i < bar[bID].len; i++) {                // 막대 제거, mark 추가
        if (--bcnt[x][y] == 0) mark.push_back({ x,y });
        x += dx[bar[bID].dir], y += dy[bar[bID].dir];
    }

    for (pii p : mark) {                                    // 제거한 막대 주변의 구역 해제
        for (int i = 0; i < 4; i++) {
            int x = p.first + dx[i], y = p.second + dy[i];
            if (bcnt[x][y] == 0) used.erase(gid[x][y]);
        }
    }
    proc();
    return used.size();
}