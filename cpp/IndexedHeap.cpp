#include <algorithm>
#define MAX_DATA 16
using namespace std;

int heapSize;

// max Heap
struct Heap {
	struct elem {
		int value;
		int idx;
	} tree[MAX_DATA];

	int heapIndex[MAX_DATA];

	void heapUp(int curIdx) {
		int parent = (curIdx - 1) / 2; // IDX 0부터 쓰겠다
		while (parent >= 0) {
			if (tree[parent].value < tree[curIdx].value) {
				swap(tree[parent], tree[curIdx]);
				heapIndex[tree[parent].idx] = parent;
				heapIndex[tree[curIdx].idx] = curIdx;
				curIdx = parent; parent = (curIdx -1) / 2;
			}
			else break;
		}
	}

	void heapDown(int curIdx) {
		int Lchild = curIdx * 2 + 1;
		int Rchild = curIdx * 2 + 2;
		int child;
		while (Lchild < heapSize) {
			if (Lchild == heapSize - 1) child = Lchild;
			else child = tree[Lchild].value > tree[Rchild].value ? Lchild : Rchild;

			if (tree[curIdx].value < tree[child].value) {
				swap(tree[curIdx], tree[child]);
				heapIndex[tree[curIdx].idx] = curIdx;
				heapIndex[tree[child].idx] = child;
				curIdx = child; Lchild = curIdx * 2 + 1; Rchild = Lchild + 1;
			}
			else break;
		}
	}

	void heapPush(int value, int idx) {
		if (heapSize > MAX_DATA) printf("FULL");
		tree[heapSize].value = value;
		tree[heapSize].idx = idx;

		heapIndex[idx] = heapSize++;
		heapUp(heapSize - 1);
	}

	int heapPop() {
		if (heapSize < 1) return -1;
		elem ret = tree[0];
		swap(tree[0], tree[--heapSize]);
		heapIndex[tree[0].idx] = 0;
		heapDown(0);
		return ret.value;
	}

	void heapUpdate(int val, int idx) {
		tree[heapIndex[idx]].value = val;
		heapUp(heapIndex[idx]);
		heapDown(heapIndex[idx]);
	}
} heap;