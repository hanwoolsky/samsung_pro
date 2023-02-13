/* 딱지를 분류해서 저장하는 구조를 vector에서 array로 변경
*/
#include<vector>
using namespace std;

const int LM = 20003;
int root[LM], rnk[LM], cnt[LM], pid[LM];
int sx[LM], sy[LM], ex[LM], ey[LM];
int pcnt[3];
int n, m;
int G[10][10][LM], gn[10][10];

int find(int x) {
    if (root[x] == x) return x;
    return root[x] = find(root[x]);
}

void union_(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return;

    pcnt[pid[x]] -= cnt[x], pcnt[pid[y]] += cnt[x];

    if (rnk[x] < rnk[y]) {
        root[x] = y;
        cnt[y] += cnt[x];
    }
    else {
        root[y] = x;
        cnt[x] += cnt[y];
        pid[x] = pid[y];

        if (rnk[x] == rnk[y]) rnk[x]++;
    }
}

void init(int N, int M)
{
    n = pcnt[1] = pcnt[2] = 0;
    m = N/10;
    for (int i = 0; i < 10; i++) for (int j = 0; j < 10; j++) gn[i][j] = 0;
}

int add(int mRow, int mCol, int mSize, int mPlayer)
{
    root[n] = n, rnk[n] = 0, cnt[n] = 1, pid[n] = mPlayer;
    pcnt[mPlayer]++;
    sx[n] = mRow, sy[n] = mCol, ex[n] = mRow + mSize - 1, ey[n] = mCol + mSize - 1;

    for (int i = sx[n] / m; i <= ex[n] / m; i++) {
        for (int j = sy[n] / m; j <= ey[n] / m; j++) {
            for (int k = 0; k < gn[i][j]; k++) {
                int c = G[i][j][k];
                if (ex[c] < sx[n] || ex[n] < sx[c] || ey[n] < sy[c] || ey[c] < sy[n]) continue;
                union_(c, n);
            }
            G[i][j][gn[i][j]++] = n;
        }
    }

    n++;
    return pcnt[mPlayer];
}

int get(int mRow, int mCol)
{
    int x = mRow / m, y = mCol / m;
    for (int i = 0; i < gn[x][y]; i++) {
        int c = G[x][y][i];
        if (sx[c] <= mRow && mRow <= ex[c] && sy[c] <= mCol && mCol <= ey[c]) return pid[find(c)];
    }
    return 0;
}