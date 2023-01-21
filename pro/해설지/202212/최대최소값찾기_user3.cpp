/*
* Sqrt Decomposition
* 실제 수열 삭제하지 않고 삭제됐다고 표시
*/
#include<algorithm>
#include<string.h>
using namespace std;

const int INF = (int)1e9;
const int LM = 200003;
const int SQ = 450;
int n;                                  // 추가된 총 원소 개수
int A[LM], exist[LM];                   // 수열 값, 존재/삭제 여부
int maxA[SQ], minA[SQ], gCnt[SQ];       // 그룹의 최대값, 최소값, 원소개수

/* A의 n번 index부터 M개의 val[] 등록*/
void add(int M, int val[]) {
    for (int i = 0; i < M; i++, n++) {
        A[n] = val[i];
        exist[n] = 1;

        int idx = n / SQ;
        gCnt[idx]++;
        maxA[idx] = max(maxA[idx], A[n]);
        minA[idx] = min(minA[idx], A[n]);
    }
}

void init(int N, int val[]) {
    n = 0;
    memset(gCnt, 0, sizeof(gCnt));      // memset()은 0, -1 만 유효
    memset(maxA, -1, sizeof(maxA));
    fill(minA, minA + SQ, INF);         // 그 외의 값은 fill()
    add(N, val);
}

/* 앞에서 K번째 값의 index를 반환*/
int getIndex(int K) {
    int idx = 0;
    for (; K>gCnt[idx]; idx++)          // 그룹 단위로 확인
        K -= gCnt[idx];

    for (int i = idx * SQ; ; i++) {     // 낱개로 확인
        K -= exist[i];
        if (K == 0) return i;
    }
}

/* idx 그룹의 min,max 새로 구하기 */
void updateMinMax(int idx) {
    int l = idx * SQ, r = min(l + SQ, n);
    minA[idx] = INF;
    maxA[idx] = -1;
    for (int i = l; i < r; i++) {
        if (!exist[i]) continue;
        minA[idx] = min(minA[idx], A[i]);
        maxA[idx] = max(maxA[idx], A[i]);
    }
}

int modified[SQ];
void erase(int s, int e) {
    int mcnt = 0;
    int cnt = e - s + 1;                        // 삭제해야하는 개수
    for (int i = getIndex(s); cnt; i++) {       // s번째 index부터 삭제
        int idx = i / SQ;

        if (gCnt[idx] == 0) {                   // 그룹에 남은 값이 없는 경우
            i = (idx+1) * SQ  - 1;              // 다음 그룹으로 이동
            continue;
        }
        if (exist[i] == 0)  continue;           // 이미 삭제된 경우 continue

        cnt--;                                  // 삭제
        exist[i] = 0;
        gCnt[idx]--;

        if (mcnt == 0 || modified[mcnt - 1] != idx) // 업데이트 된 그룹 중복 없이 등록
            modified[mcnt++] = idx;
    }

    for (int i = 0; i < mcnt; i++) {                // 업데이트 된 그롭의 min,max 값 재설정
        int idx = modified[i];
        updateMinMax(idx);
    }
}

int find(int K) {
    int maxv = -1, minv = INF;
    int idx = (n - 1) / SQ;             // 가장 마지막 그룹 선택
    for (; K>=gCnt[idx]; idx--) {       // 앞으로 이동하며 K번째 원소가 있는 그룹으로 이동
        if (gCnt[idx] == 0) continue;
        K -= gCnt[idx];              
        maxv = max(maxv, maxA[idx]);
        minv = min(minv, minA[idx]);
    }
    for (int i = min(n, (idx + 1) * SQ) - 1; K; i--) {  // 낱개로 K번째 위치까지 이동
        if (exist[i]) {
            K--;
            maxv = max(maxv, A[i]);
            minv = min(minv, A[i]);
        }
    }
    return maxv - minv;
}