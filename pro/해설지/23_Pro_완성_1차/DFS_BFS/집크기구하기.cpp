#include<string.h>
#include<vector>
using namespace std;
using pii = pair<int, int>;

int n;
int group[123][123], gcnt, gid;
char visited[123][123], vcnt;
int dx[8] = { -1,0,1,0,-1,1,1,-1 };
int dy[8] = { 0,1,0,-1,1,1,-1,-1 };
vector<pii> adj;

void init(int N)
{
	n = N;
	gcnt = vcnt = 0;
	memset(group, 0, sizeof(group));
	memset(visited, 0, sizeof(visited));
}

void update(int x, int y) {	// (x,y) ����� ��� �� �׷� ������Ʈ
	if (group[x][y] == gid || group[x][y] == 0) return;
	group[x][y] = gid;
	for (int i = 0; i < 8; i++) update(x + dx[i], y + dy[i]);
}

int count(int x, int y) {	// x,y�� ���ӵ� �� ���� ���ϱ�
	if (x<1 || x>n || y<1 || y>n) return -1;				// ������ ������ ��� ���
	if (visited[x][y] && visited[x][y] != vcnt) return -1;
	if (group[x][y] || visited[x][y] == vcnt) return 0;		// ���� ���̰ų� �̹� �湮�� ���
	visited[x][y] = vcnt;
	int cnt = 1;
	for (int i = 0; i < 4; i++) {
		int c = count(x + dx[i], y + dy[i]);
		if (c == -1) return -1;
		cnt += c;
	}
	return cnt;
}

int getSize(int row, int col) {	// �� ũ�� ���ϱ�
	memset(visited, 0, sizeof(visited));
	vcnt = 0;
	group[row][col] = gid;
	for (int i = 0; i < 4; i++) {
		vcnt++;
		int ret = count(row + dx[i], col + dy[i]);
		if (ret > 0) return ret;
	}
	return 0;
}

int play(int row, int col)
{
	adj.clear();
	gid = 0;
	for (int i = 0; i < 8; i++) {
		int x = row + dx[i];
		int y = col + dy[i];
		if (!group[x][y]) continue;

		if (gid == 0) {	// �Ȱ��� �׷� �� Ȯ���ؼ� gid�� ���
			for (pii p : adj)
				if (group[p.first][p.second] == group[x][y]) {
					gid = group[x][y];
					break;
				}
		}
		adj.push_back({ x,y });
	}

	if (adj.empty()) {
		group[row][col] = ++gcnt;
		return 0;
	}

	int ret = 0;
	if (gid) ret = getSize(row, col);
	else group[row][col] = gid = group[adj[0].first][adj[0].second];

	for (pii p : adj) update(p.first, p.second);	// ������ ��� ���� �׷��� gid�� ����
	return ret;
}