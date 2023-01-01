#include <iostream>
#include <ctime>

#define HEAP_SIZE	100

using namespace std;

typedef struct {
	int key;
} element;

typedef struct {
	element heap[HEAP_SIZE];
	int heapSize;
} Heap;

void heapPush(Heap* h, element item)
{
	int idx = ++(h->heapSize);

	while ((idx != 1) && (h->heap[idx / 2].key < item.key))
	{
		h->heap[idx] = h->heap[idx / 2];
		idx /= 2;
	}

	h->heap[idx] = item;
}

element heapPop(Heap *h)
{
	element item = h->heap[1];
	element temp = h->heap[(h->heapSize)--];
	int parent = 1;
	int child = 2;

	while (child <= h->heapSize)
	{
		if (child < h->heapSize && h->heap[child].key < h->heap[child + 1].key)
			child++;
		if (temp.key > h->heap[child].key) break;

		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}

	h->heap[parent] = temp;
	return item;
}

element heapPeek(Heap* h) { return h->heap[1]; }
int heapSize(Heap* h) { return h->heapSize; }
bool isHeapEmpty(Heap* h) { return h->heapSize == 0; }
void heapInit(Heap* h) { h->heapSize = 0; }

int main(void)
{
	Heap h;
	heapInit(&h);

	srand(time(NULL));
	for (int i = 0; i < 20; i++)
	{
		element e = { rand() % 10000 + 1 };
		heapPush(&h, e);
	}

	for (int i = 0; i < 20; i++)
		cout << heapPop(&h).key << " ";
	cout << '\n';

	return 0;
}