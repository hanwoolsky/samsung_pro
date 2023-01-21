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