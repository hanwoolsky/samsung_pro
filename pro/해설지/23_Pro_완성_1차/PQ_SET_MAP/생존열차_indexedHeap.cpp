#if 1
#include <memory.h>
using namespace std;
 
#define MAX_T   (10)
#define MAX_J   (1000)
#define MAX_M   (10000)
#define MAX_N   (100000)
 
struct Passanger
{
    int pid;
    int point;
    int jid;
    int room; // 객차 번호
    int pqidx[2]; // [0] = 내림차순, [1] = 오름차순
};
Passanger passanger[MAX_N];
int passanger_cnt;
 
int jobTable[MAX_J][200];
int job_cnt[MAX_J];
 
bool compare(int pos, register Passanger* a, register Passanger* b)
{
    if (pos == 0)
    {
        return (a->point != b->point) ? (a->point > b->point): (a->pid < b->pid);
    }
    else
    {
        return (a->point != b->point) ? (a->point < b->point) : (a->pid > b->pid);
    }
}
 
struct Heap
{
    int heapSize;
    Passanger* heap[MAX_M];
 
    void up(int current, int pos)
    {
        while (current > 0 && compare(pos, heap[current], heap[(current - 1) / 2]))
        {
            Passanger* temp = heap[current];
            heap[current] = heap[(current - 1) / 2];
            heap[(current - 1) / 2] = temp;
 
            heap[current]->pqidx[pos] = current;
            heap[(current - 1) / 2]->pqidx[pos] = (current - 1) / 2;
 
            current = (current - 1) / 2;
        }
    }
 
    void down(int current, int pos)
    {
        while (current * 2 + 1 < heapSize)
        {
            int child;
            if (current * 2 + 2 == heapSize) child = current * 2 + 1;
            else child = compare(pos, heap[current * 2 + 1], heap[current * 2 + 2]) ? current * 2 + 1 : current * 2 + 2;
 
            if (compare(pos, heap[current], heap[child])) break;
 
            Passanger* temp = heap[current];
            heap[current] = heap[child];
            heap[child] = temp;
 
            heap[current]->pqidx[pos] = current;
            heap[child]->pqidx[pos] = child;
 
            current = child;
        }
    }
 
    void heapPush(Passanger* value, int pos)
    {
        if (heapSize >= MAX_M) return;
 
        heap[heapSize] = value;
        heap[heapSize]->pqidx[pos] = heapSize;
         
        up(heapSize, pos);
        heapSize++;
    }
 
    Passanger* heapPop(int pos)
    {
        if (heapSize <= 0) return 0;
 
        heapSize--;
        Passanger* temp = heap[0];
        heap[0] = heap[heapSize];
        heap[0]->pqidx[pos] = 0;
 
        down(0, pos);
        return temp;
    }
 
    void heapUpdate(int current, int pos)
    {
        up(current, pos);
        down(current, pos);
    }
 
    void heapDelete(int current, int pos)
    {
        if (heapSize <= 0) return;
 
        heapSize--;
        if (current < heapSize)
        {
            heap[current] = heap[heapSize];
            heap[current]->pqidx[pos] = current;
            heapUpdate(current, pos);
        }
    }
 
}train[MAX_T][2]; // [0] = 내림차순, [1] = 오름차순
 
int N, M, J;
 
void init(int N, int M, int J, int mPoint[], int mJobID[])
{
    passanger_cnt = 0;
    memset(job_cnt, 0, sizeof(job_cnt));
    for (int i = 0; i < MAX_T; i++) train[i][0].heapSize = train[i][1].heapSize = 0;
 
    ::N = N;
    ::M = M;
    ::J = J;
 
    for (int i = 0; i < N; i++)
    {
        passanger[passanger_cnt] = { i, mPoint[i], mJobID[i], i / M, {0,0} };
        Passanger* temp = &passanger[passanger_cnt++];
 
        jobTable[mJobID[i]][job_cnt[mJobID[i]]++] = i;
 
        train[temp->room][0].heapPush(temp, 0);
        train[temp->room][1].heapPush(temp, 1);
    }
}
 
void destroy() { }
 
int update(int mID, int mPoint)
{
    Passanger* temp = &passanger[mID];
    temp->point += mPoint;
 
    train[temp->room][0].heapUpdate(temp->pqidx[0], 0);
    train[temp->room][1].heapUpdate(temp->pqidx[1], 1);
     
    return temp->point;
}
 
int updateByJob(int mJobID, int mPoint)
{
    int sum = 0;
    for (int i = 0; i < job_cnt[mJobID]; i++)
    {
        int pid = jobTable[mJobID][i];
        Passanger* temp = &passanger[pid];
 
        temp->point += mPoint;
        sum += temp->point;
 
        train[temp->room][0].heapUpdate(temp->pqidx[0], 0);
        train[temp->room][1].heapUpdate(temp->pqidx[1], 1);
    }
    return sum;
}
 
Passanger* changeSeat[100];
 
int move(int mNum)
{
    int sum = 0;
    int cnt = 0;
 
    for (int i = 0; i < (N / M); i++)
    {
        int change = mNum;
        if (i != 0) // 첫 번째 객차인 경우
        {
            while (train[i][0].heapSize > 0 && change-- > 0)
            {
                Passanger* temp = train[i][0].heapPop(0);
                train[i][1].heapDelete(temp->pqidx[1], 1);
                 
                sum += temp->point;
                temp->room = i - 1;
 
                changeSeat[cnt++] = temp;
            }
        }
 
        change = mNum;
        if (i != (N / M - 1)) // 마지막 객차인 경우
        {
            while (train[i][1].heapSize > 0 && change-- > 0)
            {
                Passanger* temp = train[i][1].heapPop(1);
                train[i][0].heapDelete(temp->pqidx[0], 0);
 
                sum += temp->point;
                temp->room = i + 1;
 
                changeSeat[cnt++] = temp;
            }
        }
    }
 
    for (int i = 0; i < cnt; i++)
    {
        int room = changeSeat[i]->room;
        train[room][0].heapPush(changeSeat[i], 0);
        train[room][1].heapPush(changeSeat[i], 1);
    }
 
    return sum;
}
 
#endif