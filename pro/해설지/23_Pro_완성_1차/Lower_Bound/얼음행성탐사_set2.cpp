/*
* set , lower_bound
* 초기 set에 양쪽 경계 등록 { -1, C or R }
* 현 위치와 이동하는 위치 사이에 목표 지점 있으면 종료
*/
#include<set>
using namespace std;

int R, C;
set<int> rset[700], cset[10000];	// 구조물 관리: rset[row] = {col,...}   , cset[col] = {row,..}
int visit[700][10000], vcnt;		// BFS 방문 처리: visit[r][c] = vcnt

void init(int R, int C, int N, int sRow[30000], int sCol[30000])
{
	::R = R, ::C = C;
	for (int i = 0; i < R; i++) rset[i] = { -1, C };	// 경계 등록
	for (int i = 0; i < C; i++) cset[i] = { -1, R };
	for (int i = 0; i < N; i++) {
		rset[sRow[i]].insert(sCol[i]);
		cset[sCol[i]].insert(sRow[i]);
	}
}

int head, tail;
struct Data { int r, c, d; } que[120000];	// {row, col, damage}
											// 방문 가능 위치 구조물 인접 4곳 = 30,000 * 4
void push(int r, int c, int d) {
	if (visit[r][c] == vcnt) return;
	que[tail++] = { r,c,d };
	visit[r][c] = vcnt;
}

int minDamage(int sr, int sc, int er, int ec)
{
	vcnt++;
	head = tail = 0;
	push(sr, sc, 0);
	while (head < tail) {
		int r = que[head].r;
		int c = que[head].c;
		int d = que[head++].d;

		auto rit = cset[c].lower_bound(r);				// (r,c) 바로 아래쪽 구조물 선택
		int r2 = *rit, r1 = *--rit;						// r1: 위 구조물 row, r2: 아래 구조물 row
		if (c == ec && r1 < er && er < r2) return d;	// 거치는 곳에 목표 지점이 있는 경우
		if (r1 != -1) push(r1 + 1, c, d + 1);
		if (r2 != R) push(r2 - 1, c, d + 1);


		auto cit = rset[r].lower_bound(c);				// (r,c) 바로 오른쪽 구조물 선택
		int c2 = *cit, c1 = *--cit;						// c1: 오른쪽 구조물 col, c2: 왼쪽 구조물 col
		if (r == er && c1 < ec && ec < c2) return d;	// 거치는 곳에 목표 지점이 있는 경우
		if (c1 != -1) push(r, c1 + 1, d + 1);
		if (c2 != C) push(r, c2 - 1, d + 1);
	}
	return -1;
}