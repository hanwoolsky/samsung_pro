// 762ms and wrong
#include <stdio.h>
#include <memory.h>
#include <list>
#include <string>
#include <unordered_map>
#include <set>
#define MAX_DATA_WH	9
#define MAX_SIZE 300
#define MAX_CNT 10000

using namespace std;
int honeySize;
bool honey[MAX_SIZE + 1][MAX_SIZE + 1];
int parent[MAX_SIZE*MAX_SIZE];
set<int> honeyCnt[MAX_CNT + 1];
int oddRow[6] = {-1, -1, 0, 1, 1, 0};
int oddCol[6] = {-1, 0, 1, 0, -1, -1};
int evenRow[6] = {-1, -1, 0, 1, 1, 0};
int evenCol[6] = { 0, 1, 1, 1, 0, -1 };
bool flag = 1;
list<int> honeySet[MAX_SIZE*MAX_SIZE];
unordered_map<int, string> oddLoc;
unordered_map<int, string> evenLoc;

int getID(int r, int c) {
	return (r - 1)*honeySize + c - 1;
}

void init(int N) {
	honeySize = N;
	memset(honey, 0, sizeof(honey));
	for (int i = 0; i <= MAX_CNT; i++) {
		honeyCnt[i].clear();
	}
	for (int i = 0; i < MAX_SIZE*MAX_SIZE; i++) {
		parent[i] = i;
		honeySet[i].clear();
	}
	oddLoc[-1] = "LEFT";
	oddLoc[1] = "RIGHT";
	oddLoc[-honeySize - 1] = "TL";
	oddLoc[-honeySize] = "TR";
	oddLoc[honeySize - 1] = "BL";
	oddLoc[honeySize] = "BR";
	evenLoc[-1] = "LEFT";
	evenLoc[1] = "RIGHT";
	evenLoc[-honeySize] = "TL";
	evenLoc[-honeySize + 1] = "TR";
	evenLoc[honeySize] = "BL";
	evenLoc[honeySize + 1] = "BR";
}

int findRoot(int id) {
	if (id == parent[id]) return id;

	int root = findRoot(parent[id]);
	if (root != parent[id]) {
		parent[id] = root;
	}

	return root;
}

void storeHoney(int mRow, int mCol){
	int r, c, root1, root2;
	int insertHoney = getID(mRow, mCol);
	honeySet[insertHoney].push_back(insertHoney);
	honeyCnt[1].insert(insertHoney);
	if (mRow % 2 == 1) { // 홀수
		for (int i = 0; i < 6; i++) {
			r = mRow + oddRow[i];
			c = mCol + oddCol[i];
			if (honey[r][c]) {
				root1 = findRoot(getID(r, c));
				root2 = findRoot(insertHoney);
				if (root1 < root2) { // root1이 더 왼쪽 위에 있음
					honeyCnt[honeySet[root2].size()].erase(root2);
					honeySet[root1].splice(honeySet[root1].end(), honeySet[root2]);
					honeyCnt[honeySet[root1].size()].insert(root1);
					parent[root2] = root1;
				}
				else if(root1 > root2){
					honeyCnt[honeySet[root1].size()].erase(root1);
					honeySet[root2].splice(honeySet[root2].end(), honeySet[root1]);
					honeyCnt[honeySet[root2].size()].insert(root2);
					parent[root1] = root2;
				}
			}
		}
	}
	else { // 짝수
		for (int i = 0; i < 6; i++) {
			r = mRow + evenRow[i];
			c = mCol + evenCol[i];
			if (honey[r][c]) {
				root1 = findRoot(getID(r, c));
				root2 = findRoot(insertHoney);
				if (root1 < root2) { // root1이 더 왼쪽 위에 있음
					honeyCnt[honeySet[root2].size()].erase(root2);
					honeySet[root1].splice(honeySet[root1].end(), honeySet[root2]);
					honeyCnt[honeySet[root1].size()].insert(root1);
					parent[root2] = root1;
				}
				else if (root1 > root2) {
					honeyCnt[honeySet[root1].size()].erase(root1);
					honeySet[root2].splice(honeySet[root2].end(), honeySet[root1]);
					honeyCnt[honeySet[root2].size()].insert(root2);
					parent[root1] = root2;
				}
			}
		}
	}
	honey[mRow][mCol] = 1;
}

int countShape(int mHeight, int mWidth, int mData[MAX_DATA_WH + 1][MAX_DATA_WH + 1]){
	list<int> findHoney;
	int cnt = 0;
	for (int i = 1; i <= mHeight; i++) {
		for (int j = 1; j <= mWidth; j++) {
			if (mData[i][j]) {
				findHoney.push_back(getID(i, j)); // getID말고 pair로 넣어서 비교 가능
			}
		}
    }
	for (auto qit = honeyCnt[findHoney.size()].begin(); qit != honeyCnt[findHoney.size()].end(); qit++) {
		bool flaag = 1;
		if (honeySet[*qit].size() == findHoney.size()) {
			if (honeySet[*qit].size() == 1) {
				cnt++;
				continue;
			}
			honeySet[*qit].sort();
			auto it = honeySet[*qit].begin();
			auto fit = findHoney.begin();
			bool flaag = 1;
			while (it != --honeySet[*qit].end()) {
				string diff, diff2;
				int r = *it / honeySize + 1;
				int fr = *fit / honeySize + 1;
				if (r % 2 == 1) diff = oddLoc[*next(it, 1) - *it];
				else diff = evenLoc[*next(it, 1) - *it];

				if (fr % 2 == 1) diff2 = oddLoc[*next(fit, 1) - *fit];
				else diff2 = evenLoc[*next(fit, 1) - *fit];
				if (diff != diff2) {
					flaag = 0;
					break;
				}
				it++;
				fit++;
			}
			if (flaag) cnt++;
		}
	}

	return cnt;
}

// 73ms
#include <cstring>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;
const int LM = 305;
const int ILM = 10000 + 5; // 셀 단위 밀당 최대 갯수

unordered_map<string, int> hmap; // 밀당을구성하는 <string:key, int:renum_keyID>
int keyCnt; // 밀당 모양을 기준으로 나눈 밀당모양 key 종류 수
int kidTab[LM][LM]; // (r,c)가 밀당인경우 밀당모양 keyid를 표시
int coordiTab[LM][LM]; // (r,c)가 밀당인경우 시점을 (r<<10) + c 로 표시
int tmpTab[LM][LM]; // countShape(mData[][]) 함수 호출시 mData[][]복사하여 사용

unordered_set<int> ids[ILM]; // keyid가 같은 밀당좌표( (r<<10) + c )의 모임
string key; // 방향과 경로를 이용하여 만든 문자열 ((방향*81+fr)들을 문자열로)

int dr[2][6] = { {-1,-1,0,0,1,1},{-1,-1,0,0,1,1} }; // 행번호 짝수[0][], 홀수[1][]
int dc[2][6] = { {0,1,-1,1,0,1},{-1,0,-1,1,-1,0} }; // 행번호 짝수[0][], 홀수[1][]

struct Data {
    int r, c;
} que[LM * LM]; // BFS를 위한 큐

int fr, re; // 큐의 front, rear

void init(int n) {
    memset(kidTab, 0, sizeof(kidTab)); // 셀별로 기록한 밀당모양 keyID 지우기
    memset(coordiTab, 0, sizeof(coordiTab)); // 셀별로 기록한 시점기록 지우기
    hmap.clear(); // 해시 테이블 초기화
    for (int i = 1; i <= keyCnt; ++i) ids[i].clear(); // 밀당모양별 시점목록 초기화
    keyCnt = 0; // 밀당모양 keyID갯수 초기화
}

void BFS(int r, int c, int tab[][LM]) {
    fr = re = 0;
    int i, parity, nr, nc;
    tab[r][c] = 0; // 방문하였음을 표시
    que[re++] = { r, c }; // 큐에 담기
    key = "0"; // key 만들어 가기
    while (fr < re) {
        r = que[fr].r, c = que[fr].c, parity = r % 2; // 행의 홀짝성
        for(i = 0; i < 6; ++i) {
            nr = r + dr[parity][i], nc = c + dc[parity][i];
            if (tab[nr][nc] == 0) continue;
            tab[nr][nc] = 0; // 방문하였음을 표시
            que[re++] = { nr, nc }; // 큐에 담기
            key += to_string(i * 81 + fr); // key 만들어 가기
        }
        fr++;
    }
}

void storeHoney(int mRow, int mCol) {
    int stPos = (mRow) * 1024 + mCol; // 초기 시점
    int i, kid, nr, nc, parity = mRow % 2;
    for (i = 0; i < 6; ++i) {
        nr = mRow + dr[parity][i];
        nc = mCol + dc[parity][i];
        if (kid = kidTab[nr][nc]) { // 이웃이 있다면
            stPos = min(coordiTab[nr][nc], stPos); // 시점 업데이트
            ids[kid].erase(coordiTab[nr][nc]);
        }
    }
    coordiTab[mRow][mCol] = 1; // 방문해야할 곳이므로 임시로 0이 아닌 값을 채우기
    BFS(stPos / 1024, stPos % 1024, coordiTab);

    auto rv = hmap.insert({ key, keyCnt + 1 });
    if (rv.second) ++keyCnt; // 새로운 key라면 keyCnt 증가
    kid = rv.first->second; // kid 얻기
    ids[kid].insert(stPos);
    for (i = 0; i < re; ++i) {
        kidTab[que[i].r][que[i].c] = kid; // 탐색한 전체 영역을 kid로 표시하기
        coordiTab[que[i].r][que[i].c] = stPos; // 현재 밀당모양을 이루는 각 셀에 시점을 기록
    }
}

int countShape(int mHeight, int mWidth, int mData[10][10]) {
    int i = 1, j, kid = 0;
    for (i = 1; i <= mHeight; ++i) {
        for (j = 1; j <= mWidth; ++j) tmpTab[i][j] = mData[i][j];
        tmpTab[i][j] = 0; // 경계를 비우기 : indexOutOfRange 방지를 위하여 별도처리
    }
    for (j = 1; j <= mWidth + 1; ++j) tmpTab[i][j] = 0; // 경계를 비우기 : indexOutOfRange 방지를 위하여 별도처리
    for (i = j = 1; j <= mWidth && !tmpTab[1][j]; ++j); // 모양이 시작되는 시작 위치 찾기
    BFS(1, j, tmpTab); // key구하기

    auto it = hmap.find(key); // key와 같은 모양이 있는가?
    if (it != hmap.end()) kid = it->second; // 있다면 keyID구하기
    return ids[kid].size();
}