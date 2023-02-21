#include <algorithm>
#define MAX_N 100000
#define MAX_C 10

using namespace std;

struct passenger{
    int pid;
    int jid;
    int point;
    int carNum;
    int heapHIdx;
    int heapLIdx;
} pass[MAX_N + 1];

struct heapH{
    passenger* tree[MAX_N + 1];
    int heapSize;

    void init(){
        heapSize = 0;
    }

    int comp(passenger* child, passenger* parent){
        return child->point != parent->point ? child->point > parent->point : child->pid < parent->pid; // 포인트는 크고 pid는 작은 child가 우선순위 높
    }

    void heapUp(int curIdx){
        int parent = (curIdx - 1) / 2;
        while(parent >= 0){
            if(comp(tree[curIdx], tree[parent])){
                swap(tree[curIdx], tree[parent]);
                tree[curIdx]->heapHIdx = curIdx;
                tree[parent]->heapHIdx = parent;

                curIdx = parent; parent = (curIdx - 1) / 2;
            }
            else break;
        }
    }

    void heapDown(int curIdx){
        int child;
        int Lchild = curIdx * 2 + 1;
        int Rchild = Lchild + 1;

        while(Lchild < heapSize){
            if(Lchild == heapSize - 1) child = Lchild;
            else child = comp(tree[Lchild], tree[Rchild]) ? Lchild : Rchild;

            if(comp(tree[child], tree[curIdx])){
                swap(tree[child], tree[curIdx]);
                tree[curIdx]->heapHIdx = curIdx;
                tree[child]->heapHIdx = child;

                curIdx = child; Lchild = curIdx * 2 + 1; Rchild = Lchild + 1;
            }
        }
    }

    void heapPush(passenger* data){
        tree[heapSize] = data;
        data->heapHIdx = heapSize++;
        heapUp(heapSize - 1);
    }

    passenger heapPop(){
        passenger p = *tree[0];

        tree[0] = tree[--heapSize];
        tree[0]->heapHIdx = 0;
        heapDown(0);

        return p;
    }

    void heapDelete(int idx){
        passenger p = *tree[idx];
        tree[idx] = tree[--heapSize];
        tree[idx]->heapHIdx = idx;
        heapUp(idx);
        heapDown(idx);
    }
} carH[MAX_C];

struct heapH{
    passenger* tree[MAX_N + 1];
    int heapSize;

    void init(){
        heapSize = 0;
    }

    int comp(passenger* child, passenger* parent){
        return child->point != parent->point ? child->point < parent->point : child->pid > parent->pid; // 포인트는 작고 pid는 큰 child가 우선순위 높
    }

    void heapUp(int curIdx){
        int parent = (curIdx - 1) / 2;
        while(parent >= 0){
            if(comp(tree[curIdx], tree[parent])){
                swap(tree[curIdx], tree[parent]);
                tree[curIdx]->heapLIdx = curIdx;
                tree[parent]->heapLIdx = parent;

                curIdx = parent; parent = (curIdx - 1) / 2;
            }
            else break;
        }
    }

    void heapDown(int curIdx){
        int child;
        int Lchild = curIdx * 2 + 1;
        int Rchild = Lchild + 1;

        while(Lchild < heapSize){
            if(Lchild == heapSize - 1) child = Lchild;
            else child = comp(tree[Lchild], tree[Rchild]) ? Lchild : Rchild;

            if(comp(tree[child], tree[curIdx])){
                swap(tree[child], tree[curIdx]);
                tree[curIdx]->heapLIdx = curIdx;
                tree[child]->heapLIdx = child;

                curIdx = child; Lchild = curIdx * 2 + 1; Rchild = Lchild + 1;
            }
        }
    }

    void heapPush(passenger* data){
        tree[heapSize] = data;
        data->heapLIdx = heapSize++;
        heapUp(heapSize - 1);
    }

    passenger heapPop(){
        passenger p = *tree[0];

        tree[0] = tree[--heapSize];
        tree[0]->heapLIdx = 0;
        heapDown(0);

        return p;
    }

    void heapDelete(int idx){
        passenger p = *tree[idx];
        tree[idx] = tree[--heapSize];
        tree[idx]->heapLIdx = idx;
        heapUp(idx);
        heapDown(idx);
    }
} carL[MAX_C];

void init(int N, int M, int J, int mPoint[], int mJobID[])
{

}

void destroy()
{

}

int update(int mID, int mPoint)
{
	return -1;
}

int updateByJob(int mJobID, int mPoint)
{
	return -2;
}

int move(int mNum)
{	
	return -3;
}
