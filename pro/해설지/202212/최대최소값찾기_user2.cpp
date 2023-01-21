/*
* Sqrt Decomposition
* 객체로 관리하며 실제 수열 삭제
*/
#include<algorithm>
#include<string.h>
using namespace std;

const int INF = (int)1e9;
const int LM = 200003;
const int SQ = 448;
int gn;

struct Group {
    int n, arr[SQ], minv, maxv;
    void init() { n = 0, minv = INF, maxv = -1; }

    /* O(SQ) */
    void add(int m, int val[]) {
        memcpy(arr + n, val, m * 4);
        maxv = max(maxv, *max_element(val, val + m));
        minv = min(minv, *min_element(val, val + m));
        n += m;
    }

    /* O(SQ) */
    void erase(int s, int m) {
        n -= m;
        if (n == 0) maxv = -1, minv = INF;
        else {
            memcpy(arr + s, arr + s + m, (n - s) * 4);
            maxv = *max_element(arr, arr + n);
            minv = *min_element(arr, arr + n);
        }
    }

    /* O(SQ) */
    int getMin(int m) { return *min_element(arr + n - m, arr + n); }
    int getMax(int m) { return *max_element(arr + n - m, arr + n); }
}G[SQ];

void add(int M, int val[]) {
    for (int s = 0; s < M;) {               // s = 추가해야하는 시작 index
        int m = min(SQ - G[gn].n, M - s);   // m = 마지막 그룹에 추가해야하는 원소 개수
        if (m == 0) G[++gn].init();         // 그룹에 꽉 차있는 경우 새로운 그룹 생성
        else {                              // 그룹에 val[s]부터 m개 등록
            G[gn].add(m, val + s);          
            s += m;
        }
    }
}

void init(int N, int val[]) {
    gn = 0;
    G[0].init();
    add(N, val);
}

void erase(int s, int e) {
    s--;                                        // [s, e) 삭제
    int cnt = e - s;                            // 지워야하는 개수
    for (int idx = 0; cnt; idx++) {             // idx = 그룹번호
        if (s >= G[idx].n) s -= G[idx].n;
        else {
            int m = min(cnt, G[idx].n - s);     // m = idx그룹에서 삭제하는 개수
            G[idx].erase(s, m);                 // idx그룹의 [s, s+m) 삭제
            cnt -= m;
            s = 0;
        }
    }
}

int find(int K) {
    int maxv = -1, minv = INF;
    for (int i = gn; K; i--) {
        if (G[i].n == 0) continue;
        else if (K >= G[i].n) {                     // 구간에 그룹의 모든 원소가 포함되는 경우
            maxv = max(maxv, G[i].maxv);
            minv = min(minv, G[i].minv);
            K -= G[i].n;
        }
        else {                                      // 구간에 그룹의 오른쪽 원소 일부만 포함되는 경우
            maxv = max(maxv, G[i].getMax(K));
            minv = min(minv, G[i].getMin(K));
            K = 0;
        }
    }
    return maxv - minv;
}