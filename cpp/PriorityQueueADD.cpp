#include <stdio.h>

#define MAX_SIZE 100

typedef struct _Pair{
  int key;
  int value;
} pair;

pair heap[MAX_SIZE];
int heapSize = 0;

void heapInit(void)
{
	heapSize = 0;
}

int heapPush(pair values)
{
	if (heapSize + 1 > MAX_SIZE)
	{
		printf("queue is full!");
		return 0;
	}

	heap[heapSize] = values;

	int current = heapSize;
	while (current > 0 && heap[current].key < heap[(current - 1) / 2].key) // 여기서 첫 번째 pair냐 두번째 pair냐로 비교하고
	{
		int temp = heap[(current - 1) / 2].key; // 여기서 바꿀 때 pair 끼리 바꾸면 되지 않나?
		heap[(current - 1) / 2].key = heap[current].key;
		heap[current].key = temp;
		current = (current - 1) / 2;
	}

	heapSize = heapSize + 1;

	return 1;
}

int findIndex(int value){
  for (int index = 0; index < heapSize; index++){
    if (heap[index].key == value){
      return index;
    }
  }
  return 0;
}

int update(int beforevalue, int aftervalue){
  int index = findIndex(beforevalue);
  heap[index].key = aftervalue;
  while(index > 1 && heap[index/2].key < heap[index].key){ // maxheap
    int tmp = heap[index].key;
    heap[index] = heap[index/2];
    heap[index/2].key = tmp; 
    index /= 2;
  }
}

int remove(int value){
  update(value, 100); // 100 = 1e9와 같은 max 값
  //heapPop();
  return 1;
}

int heapPop(pair *value)
{
	if (heapSize <= 0)
	{
		return -1;
	}

	*value = heap[0];
	heapSize = heapSize - 1;

	heap[0] = heap[heapSize];

	int current = 0;
	while (current * 2 + 1 < heapSize)
	{
		int child;
		if (current * 2 + 2 == heapSize)
		{
			child = current * 2 + 1;
		}
		else
		{
			child = heap[current * 2 + 1].key < heap[current * 2 + 2].key ? current * 2 + 1 : current * 2 + 2;
		}

		if (heap[current].key < heap[child].key)
		{
			break;
		}

		int temp = heap[current].key;
		heap[current] = heap[child];
		heap[child].key = temp;

		current = child;
	}
	return 1;
}

int main(int argc, char* argv[])
{
	int N;

  scanf("%d", &N);
  
  heapInit();
  
  for (int i = 0; i < N; i++)
  {
    int value;
    scanf("%d", &value);
    //heapPush(value);
  }

  for (int i = 0; i < N; i++)
  {
    int value;
    //heapPop(&value);
    printf("%d ", value);
  }
  printf("\n");
}


//maxheap, minheap, 임의 노드 remove => logn이 안될텐데?

// hash : 데이터 타입 바꾸기, 디버깅(초과 등등), 음수가 되는 경우 찾기, hash remove 구현