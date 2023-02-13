/*
j5307_TS좌석배정_user_ver01
comkiwer
non STL : union find 응용
*/
#define rint register int
const int LM = 30010;
int W, H, N;
int dr[] = {0, 1, 1, 1, 0, -1, -1, -1};
int dc[] = {1, 1, 0, -1, -1, -1, 0, 1};
struct Seat {
	int r, c, id;  // 좌표, id=r*W+c
	int flag;      // 빈좌석(0), 배점됨(1)
	int adj[8];    // 방향별 인접한 노드의 id
	void init(int nid) {
		id = nid, r = id / W, c = id % W, flag = 0;
		for (rint i = 0; i < 8; ++i) {
			int nr = r + dr[i], nc = c + dc[i];
			if (nr < 0 || nr >= H || nc < 0 || nc >= W) 
				adj[i] = -1;  // 경계를 벗어난 경우
			else 
				adj[i] = nr * W + nc; // 이웃한 id
		}
	}
}srr[LM];

inline int abs(int a) { return a < 0 ? -a : a; }
inline int max(int a, int b) { return a > b ? a : b; }
void init(int W, int H){
	::W = W, ::H = H, N = W * H;
	for (rint i = 0; i < N; ++i) srr[i].init(i);
}

int A[LM];  // 한방향으로 방문한 id목록
int selectSeat(int sn){
	if (srr[--sn].flag == 0) {   // sn 자리가 비어있는 경우
		srr[sn].flag = 1;
		return srr[sn].id + 1;
	}
	int retDist = LM, retID = -1;// 기본 결과값
	rint r = sn / W, c = sn % W; // sn의 행, 열 좌표
	rint i, j, nid;
	for (i = 0; i < 8; ++i) {
		nid = sn;
		for (j = 0; nid > -1 && srr[nid].flag; ++j) {
			A[j] = nid;          // 방문한 id를 목록에 저장
			nid = srr[nid].adj[i];
			if (nid < 0) break;
		}
		for (--j; j >= 0; --j) { // 돌아오며 인접 id 갱신 : union
			srr[A[j]].adj[i] = nid;
		}
		if (nid < 0) continue;   // 경계를 벗어난 경우
		int dist = max(abs(r - srr[nid].r), abs(c - srr[nid].c));
		if (dist < retDist)      // 더 가까운 노드라면 선택하기
			retDist = dist, retID = nid;
	}
	if (retID < 0) return 0;     // 빈 자리를 못 찾은경우
	srr[retID].flag = 1;         // 자리가 배정되었음을 표시
	return retID + 1;
}