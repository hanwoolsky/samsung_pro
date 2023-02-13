#include<string.h>
#include<string>
#include<unordered_map>
#include<algorithm>
#include<queue>
using namespace std;
using pii = pair<int, int>;

int n, L[23][23];
struct Data { int x, y, dir; };
unordered_map<int, vector<Data>> hmap;				// vector<Data> hmap[60000]
int dx[] = { 0,0,1,-1 }, dy[] = { 1,-1,0,0 };		// 우좌하상

int getKey(vector<int>&v, bool rev= 0) {				// 가장 작은 값을 1로 표현
	int minv = *min_element(v.begin(), v.end()) - 1;
	int key = 0;
	for (int i = 0; i < v.size(); i++) {
		if (rev == 0) key = key * 10 + v[i] - minv;
		else key = key * 10 + v[v.size() - i - 1] - minv;
	}
	return key;
}

int getKey2(int M, int s[]) {					// 구조물을 설치할 수 있는 땅의 고도를 가장 작은 값 1로 표현
	int maxv = *max_element(s, s + M) + 1;
	int key = 0;
	for (int i = 0; i < M; i++)
		key = key * 10 + maxv - s[i];
	return key;
}

void init(int N, int land[20][20]) {
	n = N;
	hmap.clear();
	memset(L, 0, sizeof(L));
	for (int i = 0; i < N; i++) for (int j = 0; j < N; j++)		// bfs 편의를 위해 (1,1) ~ (n,n) 으로 기록
		L[i + 1][j + 1] = land[i][j];

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			vector<int> v1, v2;
			int k1, k2;
			for (int k = j; k < j + 5 && k <= N; k++) {
				v1.push_back(L[i][k]);							// (i,j)->(i,k)
				v2.push_back(L[k][i]);							// (j,i)->(k,i)

				k1 = getKey(v1), k2 = getKey(v1, 1);			// k1: 좌->우 , k2: 우->좌
				hmap[k1].push_back({ i,j,0 });
				if (j == k) continue;							// 크기 1인 경우, 한 방향만 등록
				if (k1 != k2) hmap[k2].push_back({ i,k,1 });	// 뒤집었을 때 다른 경우만 등록

				k1 = getKey(v2), k2 = getKey(v2, 1);			// k1: 상->하 , k2: 하->상
				hmap[k1].push_back({ j,i,2 });
				if (k1 != k2) hmap[k2].push_back({ k,i,3 });
			}
		}
	}
}

int getCount(int M, int structure[5]) {
    return hmap[getKey2(M, structure)].size();
}

int bfs(int level) {			// (0,0) 을 시작으로 flood-fill
	queue<pii> q;
	bool visited[23][23] = {};
	q.push({ 0, 0 });
	visited[0][0] = 1;
	int m = n + 2;
	int remain = m * m;
	while (q.size()) {
		int x = q.front().first;
		int y = q.front().second;
		q.pop();
		remain--;
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i], ny = y + dy[i];
			if (nx < 0 || nx >= m || ny < 0 || ny >= m) continue;
			if (visited[nx][ny]) continue;
			if (L[nx][ny] >= level) continue;
			q.push({ nx,ny });
			visited[nx][ny] = 1;
		}
	}
	return remain;
}

int getMaxArea(int M, int structure[5], int seaLevel) {
	int ret = -1;
	for (Data d : hmap[getKey2(M, structure)]) {
		for (int i = 0; i < M; i++)
			L[d.x + dx[d.dir] * i][d.y + dy[d.dir] * i] += structure[i];

		ret = max(ret, bfs(seaLevel));

		for (int i = 0; i < M; i++)
			L[d.x + dx[d.dir] * i][d.y + dy[d.dir] * i] -= structure[i];
	}
    return ret;
}