#include<list>
#include<queue>
using namespace std;
using pii = pair<int, int>;

int n;
list<int> route[5];                        // line별 
list<int>::iterator iter[40003][5];

void init(int N, int start[5], int end[5])
{
    n = N;
    for (int i = 0; i < n; i++) for (int j = 0; j < 5; j++) iter[i][j] = route[j].end();
    for (int i = 0; i < 5; i++) {
        route[i].clear();
        iter[start[i]][i] = route[i].insert(route[i].end(), start[i]);
        iter[end[i]][i] = route[i].insert(route[i].end(), end[i]);
    }
}

void append(int line, int prev, int cur)
{
    iter[cur][line] = route[line].insert(next(iter[prev][line],1), cur);
}

queue<pii> q;              // { x, line }
int tick[40003][5];        // { x, line } 에 도달하는 시각
int dest;                  // 목표 지점

bool existLine(int x, int line) { return iter[x][line] != route[line].end(); }

bool push(int x, int line, int cnt) {
    if (!existLine(x,line) || tick[x][line] <= cnt) return 0;
    tick[x][line] = cnt;
    q.push({ x, line });
    return x == dest;
}

int minTime(int start, int end)
{
    if (start == end) return 0;
    for (int i = 0; i < n; i++) for (int j = 0; j < 5; j++) tick[i][j] = 5e4;
    q = {};
    dest = end;
    for (int i = 0; i < 5; i++)
        push(start, i, 0);

    while (q.size()) {
        int x = q.front().first;
        int line = q.front().second;
        q.pop();

        int newTick = tick[x][line] + 1;
        auto it = iter[x][line];
        if (it != route[line].begin() && push(*prev(it, 1), line, newTick)) return newTick;
        if (it != --route[line].end() && push(*next(it, 1), line, newTick)) return newTick;

        for (int i = 0; i < 5; i++)
            if (line != i) push(x, i, newTick);
    }

    return -1;
}

int minTransfer(int start, int end)
{
    queue<int> q;                   // line
    int cnt[5] = { 5,5,5,5,5 };     // line 도달을 위한 최소 환승 횟수

    for (int i = 0; i < 5; i++) {
        if (existLine(start, i)) {
            q.push(i);
            cnt[i] = 0;
        }
    }

    while (q.size()) {
        int line = q.front();
        q.pop();
        for (int x : route[line]) {
            if (x == end) return cnt[line];
            for (int i = 0; i < 5; i++) {
                if (cnt[i] <= cnt[line] + 1 || !existLine(x, i)) continue;
                q.push(i);
                cnt[i] = cnt[line] + 1;
            }
        }
    }

    return -1;
}