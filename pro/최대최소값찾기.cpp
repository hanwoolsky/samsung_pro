// [Linked List - 시간 초과]

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define MAX_ARR_SIZE (100000)

void init(int, int[]);
void add(int, int[]);
void erase(int, int);
int find(int);

#define CMD_INIT (100)
#define CMD_ADD  (200)
#define CMD_ERASE  (300)
#define CMD_FIND (400)

static int arr[MAX_ARR_SIZE];
static int N, M;
static int from, to;

static bool run()
{
    int query_num;
    scanf("%d", &query_num);

    int ret, ans;
    bool ok = false;

    for (int q = 0; q < query_num; q++)
    {
        int query;
        scanf("%d", &query);

        if (query == CMD_INIT)
        {
            scanf("%d", &N);
            for (int i = 0; i < N; i++)
                scanf("%d", &arr[i]);
            init(N, arr);
            ok = true;
        }
        else if (query == CMD_ADD)
        {
            scanf("%d", &M);
            for (int i = 0; i < M; i++)
                scanf("%d", &arr[i]);
            add(M, arr);
        }
        else if (query == CMD_ERASE)
        {
            scanf("%d%d", &from, &to);
            erase(from, to);

        }
        else if (query == CMD_FIND)
        {
            int K;
            scanf("%d", &K);
            ret = find(K);
            scanf("%d", &ans);

            if (ans != ret)
                ok = false;
        }
    }
    return ok;
}

//int main()
//{
//    setbuf(stdout, NULL);
//    //    freopen("sample_input.txt", "r", stdin);
//    int t, mark;
//    scanf("%d %d", &t, &mark);
//
//    for (int tc = 1; tc <= t; tc++)
//    {
//        int score = run() ? mark : 0;
//        printf("#%d %d\n", tc, score);
//    }
//    return 0;
//}

using namespace std;
#include <list>

struct DATA {
    int num;
    int maxNum;
    int minNum;
};

list<DATA> linkL;
int length = 0;

void cleanErase(int k) {
    int maxN, minN;
    auto it = linkL.end();
    it = prev(it, k);
    if (k) {
        maxN = it->maxNum;
        minN = it->minNum;
    }
    else {
        maxN = 0;
        minN = 1000000000;
    }
    it--;
    while (it != linkL.begin()) {
        if (it->num < maxN) it->maxNum = maxN;
        else {
            maxN = it->num;
            it->maxNum = maxN;
        }
        it--;
    }
    if (it->num < maxN) it->maxNum = maxN;
    else {
        maxN = it->num;
        it->maxNum = maxN;
    }

    it = next(it, length - k - 1);
    while (it != linkL.begin()) {
        if (it->num > minN) it->minNum = minN;
        else {
            minN = it->num;
            it->minNum = minN;
        }
        it--;
    }
    if (it->num > minN) it->minNum = minN;
    else {
        minN = it->num;
        it->minNum = minN;
    }
}

void clean(int k) {
    // k부터 끝까지 최대 최소 다시 정리
    auto it = linkL.end();
    it = prev(it, k);
    int maxN = it->maxNum; int minN = it->minNum;
    it--;
    
    while (it != linkL.begin()) {
        if (it->maxNum < maxN) {
            it->maxNum = maxN;
            it--;
        }
        else {
            break;
        }
    }
    if (it->maxNum < maxN) {
        it->maxNum = maxN;
    }

    it = linkL.end();
    it = prev(it, k + 1);
    while (it != linkL.begin()) {
        if (it->minNum > minN) {
            it->minNum = minN;
            it--;
        }
        else {
            break;
        }
    }
    if (it->minNum > minN) {
        it->minNum = minN;
    }
}

void init(int N, int mValue[])
{
    int maxN, minN;
    length = N;
    maxN = 0; minN = 1000000000;
    linkL.clear();
    for (int i = N - 1; i >= 0; i--) {
        if (maxN < mValue[i]) maxN = mValue[i];
        if (minN > mValue[i]) minN = mValue[i];
        linkL.push_front({ mValue[i], maxN, minN });
    }
}
void add(int M, int mValue[])
{
    int maxN, minN;
    length += M;
    maxN = 0; minN = 1000000000;
    auto it = linkL.end();
    for (int i = M - 1; i >= 0; i--) {
        if (maxN < mValue[i]) maxN = mValue[i];
        if (minN > mValue[i]) minN = mValue[i];
        linkL.insert(it, { mValue[i], maxN, minN });
        it--;
    }
    clean(M);
}

void erase(int mFrom, int mTo)
{
    length -= (mTo - mFrom + 1);
    auto it = linkL.begin();
    auto fit = next(it, mTo);
    for (it = next(it, mFrom - 1); it != fit;) {
        it = linkL.erase(it);
    }
    cleanErase(length - mFrom + 1);
}
int find(int K)
{
    auto it = linkL.end();
    it = prev(it, K);
    int ans = it->maxNum - it->minNum;

    return ans;
}

int main()
{
    int ans;
    int arr[30] = { 45, 3, 1, 19, 2, 61, 54, 8, 71, 89, 63, 67, 100, 92, 34, 18, 39, 32, 48, 63, 24, 48, 9, 73, 80, 57, 74, 98, 99, 69 };
    init(30, arr);
        
    /*int arr2[3] = { 100, 8, 99 };
    add(3, arr2);
    printf("---------------add----------------\n");
    for (auto it = linkL.begin(); it != linkL.end(); it++) {
        printf("%d (%d %d)\n", it->num, it->maxNum, it->minNum);
    }*/

    /*ans = find(5);
    printf("ans = %d\n", ans);
    ans = find(2);
    printf("ans = %d\n", ans);*/

    erase(29, 30);
    printf("---------------erase----------------\n");
    for (auto it = linkL.begin(); it != linkL.end(); it++) {
        printf("%d (%d %d)\n", it->num, it->maxNum, it->minNum);
    }
    ans = find(3);
    printf("ans = %d\n", ans);

    /*erase(9, 12);
    printf("---------------erase----------------\n");
    for (auto it = linkL.begin(); it != linkL.end(); it++) {
        printf("%d (%d %d)\n", it->num, it->maxNum, it->minNum);
    }
    ans = find(11);
    printf("ans = %d\n", ans);
    */

    int arr3[5] = { 23, 76, 23, 1, 23 };
    add(5, arr3);
    printf("---------------add----------------\n");
    for (auto it = linkL.begin(); it != linkL.end(); it++) {
        printf("%d (%d %d)\n", it->num, it->maxNum, it->minNum);
    }

    ans = find(5);
    printf("ans = %d\n", ans);
    ans = find(6);
    printf("ans = %d\n", ans);
}

// [배열]
using namespace std;
#include  <cstring>
const int LM = 200001;
 
int num[LM];
int maxNum[LM];
int minNum[LM];
int length = 0;
 
void cleanErase(int k) {
    int maxN, minN;
    if (k > length) {
        maxN = 0; minN = 1000000000;
    }
    else {
        maxN = maxNum[k - 1]; minN = minNum[k - 1];
    }
    for (int i = k - 2; i >= 0; i--) {
        if (num[i] < maxN) maxNum[i] = maxN;
        else {
            maxN = num[i];
            maxNum[i] = maxN;
        }
    }
    for (int i = k - 2; i >= 0; i--) {
        if (num[i] > minN) minNum[i] = minN;
        else {
            minN = num[i];
            minNum[i] = minN;
        };
    }
}
 
void clean(int k) {
    // k부터 끝까지 최대 최소 다시 정리
    int maxN = maxNum[length - k]; int minN = minNum[length - k];
     
    for (int i = length - k - 1; i >= 0; i--) {
        if (maxNum[i] < maxN) maxNum[i] = maxN;
        else break;
    }
    for (int i = length - k - 1; i >= 0; i--) {
        if (minNum[i] > minN) minNum[i] = minN;
        else break;
    }
}
 
void init(int N, int mValue[])
{
    int maxN, minN;
    length = N;
    maxN = 0; minN = 1000000000;
    for (int i = N - 1; i >= 0; i--) {
        if (maxN < mValue[i]) maxN = mValue[i];
        if (minN > mValue[i]) minN = mValue[i];
        num[i] = mValue[i]; maxNum[i] = maxN; minNum[i] = minN;
    }
}
 
void add(int M, int mValue[])
{
    int maxN, minN;
    maxN = 0; minN = 1000000000;
 
    for (int i = M - 1; i >= 0; i--) {
        if (maxN < mValue[i]) maxN = mValue[i];
        if (minN > mValue[i]) minN = mValue[i];
        num[length + i] = mValue[i]; maxNum[length + i] = maxN; minNum[length + i] = minN;
    }
    length += M;
    clean(M);
}
 
void erase(int mFrom, int mTo)
{
    int eraseLen = mTo - mFrom + 1;
    for (int i = mTo; i < length; i++) {
        num[i - eraseLen] = num[i];
        maxNum[i - eraseLen] = maxNum[i];
        minNum[i - eraseLen] = minNum[i];
    }
    for (int i = length - eraseLen; i < length; i++) {
        num[i] = 0; maxNum[i] = 0; minNum[i] = 0;
    }
    length -= eraseLen;
    if (mFrom > 1) cleanErase(mFrom);
}
 
int find(int K)
{
    int ans = maxNum[length - K] - minNum[length - K];
 
    return ans;
}


// Sqrt Decomposition
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

        if (mcnt == 0 || modified[mcnt - 1] != idx) // 업데이트 된 그룹 중복 없이 등록 => 전 값이 지금의 idx와 같다면 이미 등록되었다는 것 (idx는 SQ동안 계속 같으므로)
            modified[mcnt++] = idx;
    }

    for (int i = 0; i < mcnt; i++) {                // 업데이트 된 그룹의 min,max 값 재설정
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