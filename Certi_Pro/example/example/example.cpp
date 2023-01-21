#pragma warning(disable: 4996)

/***********************************************************/
// [1-1] 정렬
/***********************************************************/

#if 0
#if 0

#include <stdio.h>
#include <string.h>

// 정렬에 사용할 자료
typedef struct _score
{
	int id;
	int jumsu;
	char name[10];
}SCORE;

#define MAX_ST (10)

SCORE exam[MAX_ST] = { {10, 50, "kim"}, {2, 80, "lew"}, {8, 50, "lew"}, {4, 45, "lee"}, {1, 90, "song"},\
							   {3, 45, "kim"}, {5, 50, "song"}, {9, 100, "lee"}, {7, 75, "moon"}, {6, 90, "park"} };

int Print_All_Data(void);

int Compare_Id(SCORE* x, SCORE* y);
int Compare_Name(SCORE* x, SCORE* y);
int Compare_Jumsu(SCORE* x, SCORE* y);

int Sort_Bubble(SCORE* d, int n, int order, int (*comp)(SCORE* x, SCORE* y));
int Sort_Select(SCORE* d, int n, int order, int (*comp)(SCORE* x, SCORE* y));
int Sort_Insertion(SCORE* d, int n, int order, int (*comp)(SCORE* x, SCORE* y));
int Sort_Quick(SCORE* d, int order, int s, int e, int (*comp)(SCORE* x, SCORE* y));
int Sort_Merge(SCORE* d, SCORE* tmp, int order, int s, int e, int (*comp)(SCORE* x, SCORE* y));

int Print_All_Data(void)
{
	int i;

	for (i = 0; i < MAX_ST; i++)
	{
		printf("[%d] ID=%d, NAME=%s, SCORE=%d\n", i, exam[i].id, exam[i].name, exam[i].jumsu);
	}

	return i;
}

int Compare_Id(SCORE* x, SCORE* y)
{
	return x->id - y->id;
}

int Compare_Name(SCORE* x, SCORE* y)
{
	return strcmp(x->name, y->name);
}

int Compare_Jumsu(SCORE* x, SCORE* y)
{
	return x->jumsu - y->jumsu;
}

#endif

/***********************************************************/
// [1-1.1] Bubble Sort
/***********************************************************/

#if 0

int Sort_Bubble(SCORE* d, int n, int order, int (*comp)(SCORE* x, SCORE* y))
{
	for (int i = n - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (comp(&d[j], &d[j + 1]) * order > 0) {
				SCORE tmp = d[j]; // int tmp 아니고 SCORE tmp
				d[j] = d[j + 1];
				d[j + 1] = tmp;
			}
		}
	}
	return n;
}

#endif

#if 0

void main(void)
{
	printf("Printed Data Count = %d\n", Print_All_Data());

	printf("===================================================\n");
	printf("Sorted Data Count = %d\n", Sort_Bubble(exam, 10, 1, Compare_Id));
	printf("Printed Data Count = %d\n", Print_All_Data());
	printf("Sorted Data Count = %d\n", Sort_Bubble(exam, 10, -1, Compare_Id));
	printf("Printed Data Count = %d\n", Print_All_Data());
	printf("===================================================\n");
	printf("Sorted Data Count = %d\n", Sort_Bubble(exam, 10, 1, Compare_Name));
	printf("Printed Data Count = %d\n", Print_All_Data());
	printf("Sorted Data Count = %d\n", Sort_Bubble(exam, 10, -1, Compare_Name));
	printf("Printed Data Count = %d\n", Print_All_Data());
	printf("===================================================\n");
	printf("Sorted Data Count = %d\n", Sort_Bubble(exam, 10, 1, Compare_Jumsu));
	printf("Printed Data Count = %d\n", Print_All_Data());
	printf("Sorted Data Count = %d\n", Sort_Bubble(exam, 10, -1, Compare_Jumsu));
	printf("Printed Data Count = %d\n", Print_All_Data());
	printf("===================================================\n");
}

#endif

/***********************************************************/
// [1-1.2] Selection Sort
/***********************************************************/

#if 0

int Sort_Select(SCORE* d, int n, int order, int (*comp)(SCORE* x, SCORE* y))
{	
	int i, j;
	for (i = n - 1; i > 0; i--) {
		int max = 0;
		for (j = 1; j <= i; j++) {
			if (comp(&d[j], &d[max]) * order > 0) {
				max = j;
			}
		}
		if (max != i) {
			SCORE tmp = d[i];
			d[i] = d[max];
			d[max] = tmp;
		}
	}
	return n;
}

#endif

#if 0

void main(void)
{
	printf("Printed Data Count = %d\n", Print_All_Data());
	printf("===================================================\n");
	printf("Sorted Data Count = %d\n", Sort_Select(exam, 10, 1, Compare_Id));
	printf("Printed Data Count = %d\n", Print_All_Data());
	printf("Sorted Data Count = %d\n", Sort_Select(exam, 10, -1, Compare_Id));
	printf("Printed Data Count = %d\n", Print_All_Data());
	printf("===================================================\n");
	printf("Sorted Data Count = %d\n", Sort_Select(exam, 10, 1, Compare_Name));
	printf("Printed Data Count = %d\n", Print_All_Data());
	printf("Sorted Data Count = %d\n", Sort_Select(exam, 10, -1, Compare_Name));
	printf("Printed Data Count = %d\n", Print_All_Data());
	printf("===================================================\n");
	printf("Sorted Data Count = %d\n", Sort_Select(exam, 10, 1, Compare_Jumsu));
	printf("Printed Data Count = %d\n", Print_All_Data());
	printf("Sorted Data Count = %d\n", Sort_Select(exam, 10, -1, Compare_Jumsu));
	printf("Printed Data Count = %d\n", Print_All_Data());
	printf("===================================================\n");
}

#endif

/***********************************************************/
// [1-1.3] Insertion Sort
/***********************************************************/

#if 0

int Sort_Insertion(SCORE* d, int n, int ord, int (*comp)(SCORE* x, SCORE* y))
{
	int i, j;
	for (i = 0; i < n; i++) {
		SCORE tmp = d[i];
		for (j = i; j > 0; j--) {
			if (comp(&tmp, &d[j - 1]) * ord > 0) break;
			else d[j] = d[j - 1];
		}
		d[j] = tmp;
	}
	return n;
}

#endif

#if 0

void main(void)
{
	printf("Printed Data Count = %d\n", Print_All_Data());

	printf("===================================================\n");
	printf("Sorted Data Count = %d\n", Sort_Insertion(exam, 10, 1, Compare_Id));
	printf("Printed Data Count = %d\n", Print_All_Data());
	printf("Sorted Data Count = %d\n", Sort_Insertion(exam, 10, -1, Compare_Id));
	printf("Printed Data Count = %d\n", Print_All_Data());
	printf("===================================================\n");
	printf("Sorted Data Count = %d\n", Sort_Insertion(exam, 10, 1, Compare_Name));
	printf("Printed Data Count = %d\n", Print_All_Data());
	printf("Sorted Data Count = %d\n", Sort_Insertion(exam, 10, -1, Compare_Name));
	printf("Printed Data Count = %d\n", Print_All_Data());
	printf("===================================================\n");
	printf("Sorted Data Count = %d\n", Sort_Insertion(exam, 10, 1, Compare_Jumsu));
	printf("Printed Data Count = %d\n", Print_All_Data());
	printf("Sorted Data Count = %d\n", Sort_Insertion(exam, 10, -1, Compare_Jumsu));
	printf("Printed Data Count = %d\n", Print_All_Data());
	printf("===================================================\n");
}

#endif

/***********************************************************/
// [1-1.4] Quick Sort
/***********************************************************/

#if 0

int Sort_Quick(SCORE* d, int order, int s, int e, int (*comp)(SCORE* x, SCORE* y))
{
	if (s >= e) return 0;
	
	int pivot, high, low;
	SCORE tmp;

	pivot = e;
	for (high = s, low = s; low < e; low++) {
		if (comp(&d[low], &d[pivot]) * order < 0) {
			if (low != high) {
				tmp = d[low];
				d[low] = d[high];
				d[high] = tmp;
			}
			high++;
		}
	}
	if (pivot != high) {
		tmp = d[pivot];
		d[pivot] = d[high];
		d[high] = tmp;
	}
	Sort_Quick(d, order, s, high - 1, comp);
	Sort_Quick(d, order, high + 1, e, comp);
	return e - s + 1;
}

#endif

#if 0

void main(void)
{
	printf("Printed Data Count = %d\n", Print_All_Data());

	printf("===================================================\n");
	printf("Sorted Data Count = %d\n", Sort_Quick(exam, 1, 0, MAX_ST - 1, Compare_Id));
	printf("Printed Data Count = %d\n", Print_All_Data());
	printf("Sorted Data Count = %d\n", Sort_Quick(exam, -1, 0, MAX_ST - 1, Compare_Id));
	printf("Printed Data Count = %d\n", Print_All_Data());
	printf("===================================================\n");
	printf("Sorted Data Count = %d\n", Sort_Quick(exam, 1, 0, MAX_ST - 1, Compare_Name));
	printf("Printed Data Count = %d\n", Print_All_Data());
	printf("Sorted Data Count = %d\n", Sort_Quick(exam, -1, 0, MAX_ST - 1, Compare_Name));
	printf("Printed Data Count = %d\n", Print_All_Data());
	printf("===================================================\n");
	printf("Sorted Data Count = %d\n", Sort_Quick(exam, 1, 0, MAX_ST - 1, Compare_Jumsu));
	printf("Printed Data Count = %d\n", Print_All_Data());
	printf("Sorted Data Count = %d\n", Sort_Quick(exam, -1, 0, MAX_ST - 1, Compare_Jumsu));
	printf("Printed Data Count = %d\n", Print_All_Data());
	printf("===================================================\n");
}

#endif


/***********************************************************/
// [1-1.5] Merge Sort
/***********************************************************/

#if 0

int Sort_Merge(SCORE* d, SCORE* tmp, int order, int s, int e, int (*comp)(SCORE* x, SCORE* y))
{
	if (s >= e) return 0;
	
	// 1. 영역 나누기
	int mid = (s + e) / 2;

	// 2. 각 영역 merge sort하기
	Sort_Merge(d, tmp, order, s, mid, comp);
	Sort_Merge(d, tmp, order, mid + 1, e, comp);

	// 3. 두 영역 합치기
	int idx1 = s, idx2 = mid + 1, idxtmp = s;
	while (idx1 < mid + 1 && idx2 < e + 1) {
		if (comp(&d[idx1], &d[idx2]) * order < 0) tmp[idxtmp++] = d[idx1++];
		else tmp[idxtmp++] = d[idx2++];
	}

	// 4. 남은 부분도 마저 옮기기
	while (idx1 < mid + 1) tmp[idxtmp++] = d[idx1++];
	while (idx2 < e + 1) tmp[idxtmp++] = d[idx2++];

	// 5. 원본 배열에 넣기
	for (idxtmp = s; idxtmp < e + 1; idxtmp++) d[idxtmp] = tmp[idxtmp];
	return e - s + 1;
}

#endif

#if 0

SCORE tmp[MAX_ST];

void main(void)
{
	printf("Printed Data Count = %d\n", Print_All_Data());

	printf("===================================================\n");
	printf("Sorted Data Count = %d\n", Sort_Merge(exam, tmp, 1, 0, MAX_ST - 1, Compare_Id));
	printf("Printed Data Count = %d\n", Print_All_Data());
	printf("Sorted Data Count = %d\n", Sort_Merge(exam, tmp, -1, 0, MAX_ST - 1, Compare_Id));
	printf("Printed Data Count = %d\n", Print_All_Data());
	printf("===================================================\n");
	printf("Sorted Data Count = %d\n", Sort_Merge(exam, tmp, 1, 0, MAX_ST - 1, Compare_Name));
	printf("Printed Data Count = %d\n", Print_All_Data());
	printf("Sorted Data Count = %d\n", Sort_Merge(exam, tmp, -1, 0, MAX_ST - 1, Compare_Name));
	printf("Printed Data Count = %d\n", Print_All_Data());
	printf("===================================================\n");
	printf("Sorted Data Count = %d\n", Sort_Merge(exam, tmp, 1, 0, MAX_ST - 1, Compare_Jumsu));
	printf("Printed Data Count = %d\n", Print_All_Data());
	printf("Sorted Data Count = %d\n", Sort_Merge(exam, tmp, -1, 0, MAX_ST - 1, Compare_Jumsu));
	printf("Printed Data Count = %d\n", Print_All_Data());
	printf("===================================================\n");
}
#endif

#endif

/***********************************************************/
// [1-2] 이진 탐색
/***********************************************************/

#if 0

#if 0

#include <stdio.h>
#include <string.h>

// 정렬에 사용할 자료
typedef struct _score
{
	int id;
	int jumsu;
	char name[10];
}SCORE;

#define MAX_ST (10)

SCORE exam[MAX_ST] = { {10, 50, "kim"}, {2, 80, "lew"}, {8, 50, "lew"}, {4, 45, "lee"}, {1, 90, "song"},\
							   {3, 45, "kim"}, {5, 50, "song"}, {9, 100, "lee"}, {7, 75, "moon"}, {6, 90, "park"} };

int Print_All_Data(void);

int Compare_Id(SCORE* x, SCORE* y);
int Compare_Name(SCORE* x, SCORE* y);
int Compare_Jumsu(SCORE* x, SCORE* y);

int Sort_Bubble(SCORE* d, int n, int order, int (*comp)(SCORE* x, SCORE* y));
int Sort_Select(SCORE* d, int n, int order, int (*comp)(SCORE* x, SCORE* y));
int Sort_Insertion(SCORE* d, int n, int order, int (*comp)(SCORE* x, SCORE* y));
int Sort_Quick(SCORE* d, int order, int s, int e, int (*comp)(SCORE* x, SCORE* y));
int Sort_Merge(SCORE* d, SCORE* tmp, int order, int s, int e, int (*comp)(SCORE* x, SCORE* y));

int Print_All_Data(void)
{
	int i;

	for (i = 0; i < MAX_ST; i++)
	{
		printf("[%d] ID=%d, NAME=%s, SCORE=%d\n", i, exam[i].id, exam[i].name, exam[i].jumsu);
	}

	return i;
}

void Print_Data(int n)
{
	if ((n < 0) || (n >= MAX_ST)) return;
	printf("[%d] ID=%d, NAME=%s, SCORE=%d\n", n, exam[n].id, exam[n].name, exam[n].jumsu);
}

int Compare_Id(SCORE* x, SCORE* y)
{
	return x->id - y->id;
}

int Compare_Name(SCORE* x, SCORE* y)
{
	return strcmp(x->name, y->name);
}

int Compare_Jumsu(SCORE* x, SCORE* y)
{
	return x->jumsu - y->jumsu;
}

SCORE tmp[MAX_ST];

int Sort_Merge(SCORE* d, SCORE* tmp, int order, int s, int e, int (*comp)(SCORE* x, SCORE* y))
{
	int m, idx1, idx2, idxtmp;
	if (s >= e) return -1;

	m = (s + e) / 2;

	Sort_Merge(d, tmp, order, s, m, comp);
	Sort_Merge(d, tmp, order, m + 1, e, comp);

	idx1 = s; idx2 = m + 1; idxtmp = s;
	while (idx1 <= m && idx2 <= e)
	{
		if ((order * comp(&d[idx1], &d[idx2])) < 0) tmp[idxtmp++] = d[idx1++];
		else tmp[idxtmp++] = d[idx2++];
	}

	if (idx1 <= m) while (idx1 <= m) tmp[idxtmp++] = d[idx1++];
	else while (idx2 <= e) tmp[idxtmp++] = d[idx2++];

	for (idxtmp = s; idxtmp <= e; idxtmp++) d[idxtmp] = tmp[idxtmp];
	return e - s + 1;
}

#endif

/***********************************************************/
// [1-2.1] Binary Search 함수 설계
/***********************************************************/

#if 0

int Binary_Search(SCORE* src, int s, int e, SCORE* d, int (*comp)(SCORE* x, SCORE* y))
{
	int mid, ret;
	while (s <= e) {
		mid = (s + e) / 2;
		ret = comp(&src[mid], d);
		if (ret == 0) return mid;
		else if (ret > 0) e = mid - 1;
		else s = mid + 1;
	}
	return 0;
}
#endif


#if 0
void main(void)
{
	int ret;
	SCORE d;

	printf("Binary Search Test\n");

	printf("Exam Data(Sort by ID)\n");
	Sort_Merge(exam, tmp, 1, 0, MAX_ST - 1, Compare_Id);
	Print_All_Data();
	printf("============================================\n");

	d.id = 1;
	printf("Binary Search (ID : 1) = %d\n", ret = Binary_Search(exam, 0, MAX_ST - 1, &d, Compare_Id));
	Print_Data(ret);

	d.id = 7;
	printf("Binary Search (ID : 7) = %d\n", ret = Binary_Search(exam, 0, MAX_ST - 1, &d, Compare_Id));
	Print_Data(ret);

	d.id = 10;
	printf("Binary Search (ID : 10) = %d\n", ret = Binary_Search(exam, 0, MAX_ST - 1, &d, Compare_Id));
	Print_Data(ret);

	d.id = 15;
	printf("Binary Search (ID : 15) = %d\n", ret = Binary_Search(exam, 0, MAX_ST - 1, &d, Compare_Id));
	Print_Data(ret);
	printf("============================================\n");

	printf("Exam Data(Sort by Name)\n");
	Sort_Merge(exam, tmp, 1, 0, MAX_ST - 1, Compare_Name);
	Print_All_Data();
	printf("============================================\n");

	strcpy(d.name, "moon");
	printf("Binary Search (Name : moon) = %d\n", ret = Binary_Search(exam, 0, MAX_ST - 1, &d, Compare_Name));
	Print_Data(ret);

	strcpy(d.name, "kim");
	printf("Binary Search (Name : kim) = %d\n", ret = Binary_Search(exam, 0, MAX_ST - 1, &d, Compare_Name));
	Print_Data(ret);

	strcpy(d.name, "song");
	printf("Binary Search (Name : song) = %d\n", ret = Binary_Search(exam, 0, MAX_ST - 1, &d, Compare_Name));
	Print_Data(ret);

	strcpy(d.name, "choi");
	printf("Binary Search (Name : choi) = %d\n", ret = Binary_Search(exam, 0, MAX_ST - 1, &d, Compare_Name));
	Print_Data(ret);
	printf("============================================\n");

}
#endif

/***********************************************************/
// [1-2.2] Binary Search 기반 Lower bound 탐색 함수 설계
/***********************************************************/

#if 0
int Binary_Search_Lower(SCORE* src, int s, int e, SCORE* d, int (*comp)(SCORE* x, SCORE* y))
{
	int mid, ret, sol = -1;
	while (s <= e) {
		mid = (s + e) / 2;
		ret = comp(&src[mid], d);
		if (ret >= 0) {
			sol = mid;
			e = mid - 1;
		} else{
			s = mid + 1;
		}
	}
	return sol;
}
#endif

/***********************************************************/
// [1-2.3] Binary Search 기반 Uppwer bound 탐색 함수 설계
/***********************************************************/
#if 0
int Binary_Search_Upper(SCORE* src, int s, int e, SCORE* d, int (*comp)(SCORE* x, SCORE* y))
{
	int mid, ret, sol = -1;
	while (s <= e) {
		mid = (s + e) / 2;
		ret = comp(&src[mid], d);
		if (ret <= 0) {
			sol = mid;
			s = mid + 1;
		}
		else {
			e = mid - 1;
		}
	}
	return sol;
}
#endif


#if 0
void main(void)
{
	int i;
	int lower, upper;
	SCORE ld, ud;

	printf("Binary Search Test(Upper, Lower bound)\n");

	printf("Exam Data(Sort by jumsu)\n");
	Sort_Merge(exam, tmp, 1, 0, MAX_ST - 1, Compare_Jumsu);
	Print_All_Data();
	printf("============================================\n");

	ld.jumsu = 75;
	ud.jumsu = 100;
	lower = Binary_Search_Lower(exam, 0, MAX_ST - 1, &ld, Compare_Jumsu);
	upper = Binary_Search_Upper(exam, 0, MAX_ST - 1, &ud, Compare_Jumsu);
	printf("Binary Search (Jumsu : 75~100) = (%d,%d)\n", lower, upper);
	for (i = lower; i <= upper; i++)
	{
		Print_Data(i);
	}

	ld.jumsu = 0;
	ud.jumsu = 74;
	lower = Binary_Search_Lower(exam, 0, MAX_ST - 1, &ld, Compare_Jumsu);
	upper = Binary_Search_Upper(exam, 0, MAX_ST - 1, &ud, Compare_Jumsu);
	printf("Binary Search (Jumsu : 0~74) = (%d,%d)\n", lower, upper);
	for (i = lower; i <= upper; i++)
	{
		Print_Data(i);
	}

	ld.jumsu = 51;
	ud.jumsu = 74;
	lower = Binary_Search_Lower(exam, 0, MAX_ST - 1, &ld, Compare_Jumsu);
	upper = Binary_Search_Upper(exam, 0, MAX_ST - 1, &ud, Compare_Jumsu);
	printf("Binary Search (Jumsu : 51~74) = (%d,%d)\n", lower, upper);
}
#endif

#endif

/***********************************************************/
// [1-3.1] 선형리스트 - stack
/***********************************************************/

#if 0

#include <stdio.h>

#define MAX_STACK		10
#define STACK_EMPTY	MAX_STACK
#define STACK_FULL		0

int Push_Stack(int data);
int Pop_Stack(int* p);
int Print_Stack(void);
int Count_Full_Data_Stack(void);
int Count_Empty_Data_Stack(void);

int a[MAX_STACK + 1] = { 1,2,3,4,5,6,7,8,9,10,11 };
int Stack[MAX_STACK];
int Sptr = STACK_EMPTY;

int Push_Stack(int data)
{
	if (Sptr == STACK_FULL) return -1;
	else Stack[--Sptr] = data;
	return 1;
}

int Pop_Stack(int* p)
{
	if (Sptr == STACK_EMPTY) return -1;
	else *p = Stack[Sptr++];
	return *p;
}

int Print_Stack(void)
{
	int i;

	for (i = Sptr; i < MAX_STACK; i++)
	{
		printf("STACK[%d] = %d\n", i, Stack[i]);
	}

	return MAX_STACK - Sptr;
}

int Count_Full_Data_Stack(void)
{
	return STACK_EMPTY - Sptr;
}

int Count_Empty_Data_Stack(void)
{
	return Sptr - STACK_FULL;
}

void main(void)
{
	int i;

	for (i = 0; i < (MAX_STACK + 1); i++)
	{
		printf("%d, ", a[i]);
	}

	printf("\n");

	for (i = 0; i < 5; i++)
	{
		printf("Push Result = %d\n", Push_Stack(a[i]));
		printf("Print Result = %d, ", Print_Stack());
		printf("Full = %d ", Count_Full_Data_Stack());
		printf("Empty = %d\n", Count_Empty_Data_Stack());
		printf("Sptr = %d\n", Sptr);
	}

	for (i = 0; i < 5; i++)
	{
		printf("Pop Result = %d\n", Pop_Stack(&a[i]));
		printf("Print Result = %d, ", Print_Stack());
		printf("Full = %d ", Count_Full_Data_Stack());
		printf("Empty = %d\n", Count_Empty_Data_Stack());
		printf("Sptr = %d\n", Sptr);
	}

	for (i = 0; i < (MAX_STACK + 1); i++)
	{
		printf("%d, ", a[i]);
	}

	printf("\n");

	for (i = 0; i < (MAX_STACK + 1); i++)
	{
		printf("Push Result = %d\n", Push_Stack(a[i]));
		printf("Print Result = %d, ", Print_Stack());
		printf("Full = %d ", Count_Full_Data_Stack());
		printf("Empty = %d\n", Count_Empty_Data_Stack());
		printf("Sptr = %d\n", Sptr);
	}

	for (i = 0; i < (MAX_STACK + 1); i++)
	{
		printf("Pop Result = %d\n", Pop_Stack(&a[i]));
		printf("Print Result = %d, ", Print_Stack());
		printf("Full = %d ", Count_Full_Data_Stack());
		printf("Empty = %d\n", Count_Empty_Data_Stack());
		printf("Sptr = %d\n", Sptr);
	}

	for (i = 0; i < (MAX_STACK + 1); i++)
	{
		printf("%d, ", a[i]);
	}

	printf("\n");
}

#endif

/***********************************************************/
// [1-3.2] 선형리스트 - Linear Queue
/***********************************************************/

#if 0

#include <stdio.h>

#define MAX_Q			5
#define Q_EMPTY		0
#define Q_FULL			MAX_Q

int In_Queue(int data);
int Out_Queue(int* p);
int Print_Queue(void);
int Count_Full_Data_Queue(void);
int Count_Empty_Data_Queue(void);

int a[MAX_Q + 1] = { 1,2,3,4,5,6 };
int Queue[MAX_Q];
int Wrptr = Q_EMPTY;
int Rdptr = Q_EMPTY;

int In_Queue(int data)
{



}

int Out_Queue(int* p)
{





}

int Print_Queue(void)
{
	int i;

	for (i = Rdptr; i < Wrptr; i++)
	{
		printf("Queue[%d] = %d\n", i, Queue[i]);
	}

	return Wrptr - Rdptr;
}

int Count_Full_Data_Queue(void)
{
	return Wrptr - Rdptr;
}

int Count_Empty_Data_Queue(void)
{
	return MAX_Q - (Wrptr - Rdptr);
}

void main(void)
{
	int i;

	for (i = 0; i < (MAX_Q + 1); i++)
	{
		printf("%d, ", a[i]);
	}

	printf("\n");

	for (i = 0; i < 3; i++)
	{
		printf("Queue Result = %d\n", In_Queue(a[i]));
		printf("Print Result = %d, ", Print_Queue());
		printf("Full = %d ", Count_Full_Data_Queue());
		printf("Empty = %d\n", Count_Empty_Data_Queue());
		printf("Wrptr = %d, Rdptr = %d\n", Wrptr, Rdptr);
	}

	for (i = 0; i < 3; i++)
	{
		a[i] = 0;
	}

	for (i = 0; i < 3; i++)
	{
		printf("Dequeue Result = %d\n", Out_Queue(&a[i]));
		printf("Print Result = %d, ", Print_Queue());
		printf("Full = %d ", Count_Full_Data_Queue());
		printf("Empty = %d\n", Count_Empty_Data_Queue());
		printf("Wrptr = %d, Rdptr = %d\n", Wrptr, Rdptr);
	}

	for (i = 0; i < (MAX_Q + 1); i++)
	{
		printf("%d, ", a[i]);
	}

	printf("\n");

	for (i = 0; i < (MAX_Q + 1); i++)
	{
		printf("Queue Result = %d\n", In_Queue(a[i]));
		printf("Print Result = %d, ", Print_Queue());
		printf("Full = %d ", Count_Full_Data_Queue());
		printf("Empty = %d\n", Count_Empty_Data_Queue());
		printf("Wrptr = %d, Rdptr = %d\n", Wrptr, Rdptr);
	}

	for (i = 0; i < (MAX_Q + 1); i++)
	{
		a[i] = 0;
	}

	for (i = 0; i < (MAX_Q + 1); i++)
	{
		printf("Dequeue Result = %d\n", Out_Queue(&a[i]));
		printf("Print Result = %d, ", Print_Queue());
		printf("Full = %d ", Count_Full_Data_Queue());
		printf("Empty = %d\n", Count_Empty_Data_Queue());
		printf("Wrptr = %d, Rdptr = %d\n", Wrptr, Rdptr);
	}

	for (i = 0; i < (MAX_Q + 1); i++)
	{
		printf("%d, ", a[i]);
	}

	printf("\n");
}

#endif

/***********************************************************/
// [1-3.3] 선형 리스트 - Circular Queue
/***********************************************************/

#if 0

#include <stdio.h>

#define MAX_Q		8 // 실제로 저장할 수 있는 데이터의 개수는 7개
#define Q_MIN		0
#define Q_MAX		MAX_Q

int In_Queue(int data);
int Out_Queue(int* p);
int Print_Queue(void);
int Count_Full_Data_Queue(void);
int Count_Empty_Data_Queue(void);

int a[MAX_Q + 1] = { 1,2,3,4,5,6,7,8,9 };
int Queue[MAX_Q];
int Wrptr = Q_MIN;
int Rdptr = Q_MIN;

int In_Queue(int data)
{
	if ((Wrptr + 1) % MAX_Q == Rdptr) return -1;
	Queue[Wrptr] = data;
	Wrptr = (Wrptr + 1) % MAX_Q;
	return 1;
}

int Out_Queue(int* p)
{
	if (Rdptr == Wrptr) return -1;
	*p = Queue[Rdptr];
	Rdptr = (Rdptr + 1) % MAX_Q;
	return 1; // return을 안 쓰면 Rdptr값이 출력된다. why? => 마지막에 저장된 eax값(cpu, compiler에 따라 다름)을 출력
}

int Print_Queue(void)
{
	int i;
	int rd = Rdptr;
	int n = Count_Full_Data_Queue();

	for (i = 0; i < n; i++)
	{
		printf("Queue[%d] = %d\n", rd, Queue[rd++]);
		rd %= MAX_Q;
	}

	return n;
}

int Count_Full_Data_Queue(void)
{
	if (Rdptr > Wrptr) return MAX_Q - (Rdptr - Wrptr);
	return Wrptr - Rdptr;
}

int Count_Empty_Data_Queue(void)
{
	return MAX_Q - Count_Full_Data_Queue() - 1;
}

void main(void)
{
	int i;

	for (i = 0; i < (MAX_Q + 1); i++)
	{
		printf("%d, ", a[i]);
	}

	printf("\n");

	for (i = 0; i < 3; i++)
	{
		printf("Queue Result = %d\n", In_Queue(a[i]));
		printf("Print Result = %d, ", Print_Queue());
		printf("Full = %d ", Count_Full_Data_Queue());
		printf("Empty = %d\n", Count_Empty_Data_Queue());
		printf("Wrptr = %d, Rdptr = %d\n", Wrptr, Rdptr);
	}

	for (i = 0; i < 3; i++)
	{
		a[i] = 0;
	}

	for (i = 0; i < 3; i++)
	{
		printf("Dequeue Result = %d\n", Out_Queue(&a[i]));
		printf("Print Result = %d, ", Print_Queue());
		printf("Full = %d ", Count_Full_Data_Queue());
		printf("Empty = %d\n", Count_Empty_Data_Queue());
		printf("Wrptr = %d, Rdptr = %d\n", Wrptr, Rdptr);
	}

	for (i = 0; i < (MAX_Q + 1); i++)
	{
		printf("%d, ", a[i]);
	}

	printf("\n");

	for (i = 0; i < (MAX_Q + 1); i++)
	{
		printf("Queue Result = %d\n", In_Queue(a[i]));
		printf("Print Result = %d, ", Print_Queue());
		printf("Full = %d ", Count_Full_Data_Queue());
		printf("Empty = %d\n", Count_Empty_Data_Queue());
		printf("Wrptr = %d, Rdptr = %d\n", Wrptr, Rdptr);
	}

	for (i = 0; i < (MAX_Q + 1); i++)
	{
		a[i] = 0;
	}

	for (i = 0; i < (MAX_Q + 1); i++)
	{
		printf("Dequeue Result = %d\n", Out_Queue(&a[i]));
		printf("Print Result = %d, ", Print_Queue());
		printf("Full = %d ", Count_Full_Data_Queue());
		printf("Empty = %d\n", Count_Empty_Data_Queue());
		printf("Wrptr = %d, Rdptr = %d\n", Wrptr, Rdptr);
	}

	for (i = 0; i < (MAX_Q + 1); i++)
	{
		printf("%d, ", a[i]);
	}

	printf("\n");
}

#endif

/***********************************************************/
// [1-4] Linked List
/***********************************************************/

/***********************************************************/
// [1-4-1] 배열 기반 연결 리스트
/***********************************************************/

#if 0

/***********************************************************/
// [1-4-1.1] 데이터 모델링
/***********************************************************/

#if 0

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <malloc.h>

typedef struct _score
{
	int id;
	int jumsu;
	char name[10];
	struct _score* next;
}SCORE;

SCORE Head;

#define MAX_ST		20

SCORE exam[MAX_ST];

// 이제부터 설계되는 모든 함수는 이 부분에 선언을 추가한다.
int Print_All_Data(void);
int Print_Data(int no);
int Count_Data(void);
int Create_Data(SCORE* p);
int Insert_Data(SCORE* p);
int Insert_Node(SCORE* head, SCORE* d);
int Print_All_Node(SCORE* head);
SCORE* Search_Id_Node(SCORE* head, int id);
int Count_Node(SCORE* head);
int Print_Node(SCORE* head, int id);
int Delete_Node(SCORE* head, int id);
int Copy_All_Node(SCORE* head, SCORE* buf);
int Count_Name_Node(SCORE* head, char* name);
int Count_Score_Node(SCORE* head, int jumsu);
int Copy_Name_Node(SCORE* head, char* name, SCORE* buf);
int Copy_Score_Node(SCORE* head, int jumsu, SCORE* buf);

SCORE test[MAX_ST] = { {10, 50, "kim"}, {2, 80, "lew"}, {8, 50, "lew"}, {4, 45, "lee"}, {1, 90, "song"},\
							   {3, 45, "kim"}, {5, 50, "song"}, {9, 100, "lee"}, {7, 75, "moon"}, {6, 90, "park"}, \
							   {15, 90, "ki"}, {11, 20, "kong"}, {14, 40, "shin"}, {12, 50, "son"}, {17, 48, "lee"}, \
							   {20, 100, "min"}, {19, 80, "you"}, {13, 45, "song"}, {16, 54, "no"}, {18, 100, "yang"} };

void Make_Test_Data(int n)
{
	int i;

	for (i = 0; i < n; i++)
	{
		exam[i] = test[i];
	}
}

#endif

/***********************************************************/
// [1-4-1.2] 데이터 생성, 인쇄, 함수 설계
/***********************************************************/

#if 0

int Create_Data(SCORE* p)
{
	printf("\n사번을 입력하세요. => ");
	scanf("%d", &p->id);
	fflush(stdin);
	printf("이름을 입력하세요. => ");
	scanf("%s", p->name);
	fflush(stdin);
	printf("점수를 입력하세요. => ");
	scanf("%d", &p->jumsu);
	fflush(stdin);
	p->next = (SCORE*)0x0;

	return 1;
}

int Print_All_Data(void)
{
	int i;

	printf("Head.next = 0x%.8X\n", Head.next);

	for (i = 0; i < MAX_ST; i++)
	{
		if (exam[i].id == 0) break;
		printf("[%d] addr = 0x%.8X, ID=%d, NAME=%s, SCORE=%d, next = 0x%.8X\n", i, &exam[i], exam[i].id, exam[i].name, exam[i].jumsu, exam[i].next);
	}

	return i;
}

int Print_Data(int no)
{
	if (exam[no].id == 0) return -1;
	printf("[%d] addr = 0x%.8X, ID=%d, NAME=%s, SCORE=%d, next = 0x%.8X\n", &exam[no], exam[no].id, exam[no].name, exam[no].jumsu, exam[no].next);
	return 1;
}

int Count_Data(void)
{
	int i;

	for (i = 0; i < MAX_ST; i++)
	{
		if (exam[i].id == 0) break;
	}

	return i;
}

int Insert_Data(SCORE* p)
{
	int i, e = -1;

	for (i = 0; i < MAX_ST; i++)
	{
		if (e == -1 && exam[i].id == 0)
		{
			e = i;
		}

		if (exam[i].id == p->id)
		{
			return -2;
		}
	}
	if (e != -1) {
		exam[e] = (*p);
	}

	return -1;
}

#endif

/***********************************************************/
// [1-4-1.3] 데이터 하나를 생성하여 Linked List에 추가하는 함수
/***********************************************************/

#if 0

int Insert_Node(SCORE* head, SCORE* d)
{
	// 노드를 추가할 위치 탐색
	SCORE* prev = head; // head의 주소부터 시작
	while (prev->next) {
		if (prev->next->id > d->id) break; // while문 밖에서 추가 (맨 뒤에 추가해야하는 경우와 합치기 위해)
		else if (d->id == prev->next->id) return -2;
		prev = prev->next;
	}
	d->next = prev->next;
	prev->next = d;

	return 1;
}

#endif

#if 0

void main(void)
{
	int i;
	int r;

	for (i = 0; i < 8; i++)
	{
		printf("[Loop: %d] Insert Result = %d\n", i, r = Insert_Data(&test[i]));
		printf("Printed Data Count = %d\n", Print_All_Data());
		printf("Insert Node Result = %d\n", Insert_Node(&Head, &exam[r]));
		printf("Printed Data Count = %d\n", Print_All_Data());
	}
}

#endif

/***********************************************************/
// [1-4-1.4] link에 따라서 각 노드의 정보를 인쇄하도록 함수
/***********************************************************/
/***********************************************************/
// [1-4-1.5] link에 따라서 주어진 사번에 맞는 노드를 찾아 주소를 리턴하는 함수
/***********************************************************/

#if 0

int Print_All_Node(SCORE* head)
{
	int cnt = 0;
	SCORE* node = head->next;
	while (node) {
		printf("addr = 0x%.8X, ID=%d, NAME=%s, SCORE=%d, next = 0x%.8X\n", node, node->id, node->name, node->jumsu, node->next);
		cnt++;
		node = node->next;
	}
	return cnt;
}

SCORE* Search_Id_Node(SCORE* head, int id)
{
	SCORE* node = head->next;
	while (node) {
		if (node->id == id) return node;
		node = node->next;
	}
	return (SCORE*)0;
}

#endif

#if 0

void main(void)
{
	int i;
	int r;
	SCORE* p;

	for (i = 0; i < 8; i++)
	{
		printf("[Loop: %d] Insert Result = %d\n", i, r = Insert_Data(&test[i]));
		printf("Printed Data Count = %d\n", Print_All_Data());
		printf("Insert Node Result = %d\n", Insert_Node(&Head, &exam[r]));
		printf("Printed Node Count = %d\n", Print_All_Node(&Head));
	}

	printf("Searched Node Address = 0x%.8X\n", p = Search_Id_Node(&Head, 8));

	if (p != (SCORE*)0x0)
	{
		printf("ID=%d, NAME=%s, SCORE=%d, next = 0x%.8X\n", p->id, p->name, p->jumsu, p->next);
	}

	printf("Searched Node Address = 0x%.8X\n", p = Search_Id_Node(&Head, 7));

	if (p != (SCORE*)0x0)
	{
		printf("ID=%d, NAME=%s, SCORE=%d, next = 0x%.8X\n", p->id, p->name, p->jumsu, p->next);
	}
}

#endif

/***********************************************************/
// [1-4-1.6] list에 저장된 자료의 총합을 계산하는 함수
/***********************************************************/

#if 0

int Count_Node(SCORE* head)
{
	int cnt = 0;
	SCORE* node = head->next;
	while (node) {
		cnt++;
		node = node->next;
	}
	return cnt;
}

#endif

/***********************************************************/
// [1-4-1.7] link에 따라서 주어진 사번에 맞는 자료를 인쇄하는 함수
/***********************************************************/

#if 0

int Print_Node(SCORE* head, int id)
{
	SCORE* node = Search_Id_Node(head, id);
	if (node == (SCORE*)0) return -1;
	printf("addr = 0x%.8X, ID=%d, NAME=%s, SCORE=%d, next = 0x%.8X\n", node, node->id, node->name, node->jumsu, node->next);
	return 1;
}

#endif

#if 0

void main(void)
{
	int i;
	int r;

	for (i = 0; i < 8; i++)
	{
		printf("[Loop: %d] Insert Result = %d\n", i, r = Insert_Data(&test[i]));
		printf("Printed Data Count = %d\n", Print_All_Data());
		printf("Insert Node Result = %d\n", Insert_Node(&Head, &exam[r]));
		printf("Printed Node Count = %d\n", Print_All_Node(&Head));
		printf("Node Count = %d\n", Count_Node(&Head));
	}

	printf("Print Node Result = %d\n", Print_Node(&Head, 8));
	printf("Print Node Result = %d\n", Print_Node(&Head, 7));
}

#endif

/***********************************************************/
// [1-4-1.8] link에 따라서 주어진 사번의 node를 찾아서 삭제하는 함수
/***********************************************************/

#if 0

int Delete_Node(SCORE* head, int id)
{
	SCORE* prev = head;
	while (prev->next) {
		if (prev->next->id == id) {
			prev->next->id = 0;
			prev->next = prev->next->next;
			return 1;
		}
		prev = prev->next;
	}
	return -1;
}

#endif

#if 0

void main(void)
{
	int i;
	int r;

	for (i = 0; i < 8; i++)
	{
		printf("[Loop: %d] Insert Result = %d\n", i, r = Insert_Data(&test[i]));
		printf("Insert Node Result = %d\n", Insert_Node(&Head, &exam[r]));
	}

	printf("Printed Node Count = %d\n", Print_All_Node(&Head));
	printf("Delete Node Result = %d\n", Delete_Node(&Head, 8));
	printf("Delete Node Result = %d\n", Delete_Node(&Head, 7));
	printf("Delete Node Result = %d\n", Delete_Node(&Head, 1));
	printf("Delete Node Result = %d\n", Delete_Node(&Head, 10));
	printf("Printed Node Count = %d\n", Print_All_Node(&Head));
}

#endif

/***********************************************************/
// [1-4-1.9] 주어진 버퍼에 자료를 모두 복사해 주는 함수
/***********************************************************/

#if 0

int Copy_All_Node(SCORE* head, SCORE* buf)
{
	int cnt = 0;
	SCORE* node = head->next;
	while (node) {
		buf[cnt] = *node;
		buf[cnt].next = &buf[cnt + 1];
		cnt++;
	}
	if (cnt > 0) {
		buf[cnt - 1].next = (SCORE*)0;
		return cnt;
	}
}

#endif

#if 0

void main(void)
{
	int i;
	int r;
	SCORE* p;
	SCORE new_head;

	for (i = 0; i < 8; i++)
	{
		printf("[Loop: %d] Insert Result = %d\n", i, r = Insert_Data(&test[i]));
		printf("Insert Node Result = %d\n", Insert_Node(&Head, &exam[r]));
	}

	printf("Printed Node Count = %d\n", Print_All_Node(&Head));
	printf("Node Count = %d\n", r = Count_Node(&Head));

	p = calloc(r, sizeof(SCORE));
	printf("Copy All Node Result = %d\n", Copy_All_Node(&Head, p));
	new_head.next = p;
	printf("Printed Node Count = %d\n", Print_All_Node(&new_head));
	free(p);
}

#endif

/***********************************************************/
// [1-4-1.10] node에서 요청한 자료의 수를 계수하거나 버퍼에 복사해 주는 함수
/***********************************************************/

#if 0

int Count_Name_Node(SCORE* head, char* name)
{
	int n = 0;

	if (head->next == (SCORE*)0x0) return 0;
	head = head->next;

	for (;;)
	{
		if (!strcmp(head->name, name)) n++;
		if (head->next == (SCORE*)0x0) return n;
		head = head->next;
	}
}

int Count_Score_Node(SCORE* head, int jumsu)
{
	int n = 0;

	if (head->next == (SCORE*)0x0) return 0;
	head = head->next;

	for (;;)
	{
		if (head->jumsu == jumsu) n++;
		if (head->next == (SCORE*)0x0) return n;
		head = head->next;
	}
}

int Copy_Name_Node(SCORE* head, char* name, SCORE* buf)
{
	int cnt = 0;
	SCORE* node = head->next;

	while (node) {
		if (strcmp(node->name, name) == 0) {
			buf[cnt] = *node;
			buf[cnt].next = &buf[cnt + 1];
			cnt++;
		}

		node = node->next;
	}

	if (cnt > 0) {
		buf[cnt - 1].next = (SCORE*)0;
		return cnt;
	}
	else return -1;
}

int Copy_Score_Node(SCORE* head, int jumsu, SCORE* buf)
{
	int cnt = 0;
	SCORE* node = head->next;

	while (node) {
		if (node->jumsu == jumsu) {
			buf[cnt] = *node;
			buf[cnt].next = &buf[cnt + 1];
			cnt++;
		}

		node = node->next;
	}

	if (cnt > 0) {
		buf[cnt - 1].next = (SCORE*)0;
		return cnt;
	}
	else return -1;
}

#endif

#if 0

void main(void)
{
	int i;
	int r;
	SCORE* p;
	SCORE new_head;

	for (i = 0; i < 20; i++)
	{
		printf("[Loop: %d] Insert Result = %d\n", i, r = Insert_Data(&test[i]));
		printf("Insert Node Result = %d\n", Insert_Node(&Head, &exam[r]));
	}

	printf("Printed Node Count = %d\n", Print_All_Node(&Head));

	printf("Name Node Count = %d\n", r = Count_Name_Node(&Head, "lew"));
	p = calloc(r, sizeof(SCORE));
	printf("Copy Name Node Result = %d\n", Copy_Name_Node(&Head, "lew", p));
	new_head.next = p;
	printf("Printed Node Count = %d\n", Print_All_Node(&new_head));
	free(p);

	printf("Score Node Count = %d\n", r = Count_Score_Node(&Head, 100));
	p = calloc(r, sizeof(SCORE));
	printf("Copy Score Node Result = %d\n", Copy_Score_Node(&Head, 100, p));
	new_head.next = p;
	printf("Printed Node Count = %d\n", Print_All_Node(&new_head));
	free(p);
}

#endif


#endif

/***********************************************************/
// [1-4-2] 배열 기반 연결리스트 - 더블 링크
/***********************************************************/

#if 0

/***********************************************************/
// [1-4-2.1] 기존 Linked List 방식 중 그대로 사용하는 함수들
// 단, 인쇄할 때 Prev Node 값도 인쇄하도록 추가한다.
/***********************************************************/

#if 0

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <malloc.h>

typedef struct _score
{
	int id;
	int jumsu;
	char name[10];
	struct _score* next;
	struct _score* prev;
}SCORE;

SCORE Head;

#define MAX_ST		20

SCORE exam[MAX_ST];

int Print_All_Data(void);
int Print_Data(int no);
int Count_Data(void);
int Create_Data(SCORE* p);
int Insert_Data(SCORE* p);
int Insert_Node(SCORE* head, SCORE* d);
int Print_All_Node(SCORE* head);
int Print_All_Node_Reverse(SCORE* head);
SCORE* Search_Id_Node(SCORE* head, int id);
int Count_Node(SCORE* head);
int Print_Node(SCORE* head, int id);
int Delete_Node(SCORE* head, int id);
int Copy_All_Node(SCORE* head, SCORE* buf);
int Count_Name_Node(SCORE* head, char* name);
int Count_Score_Node(SCORE* head, int jumsu);
int Copy_Name_Node(SCORE* head, char* name, SCORE* buf);
int Copy_Score_Node(SCORE* head, int jumsu, SCORE* buf);
int Print_Selected_Node(SCORE* head, int id, int num);
int Print_Selected_Node_Reverse(SCORE* head, int id, int num);

SCORE test[MAX_ST] = { {10, 50, "kim"}, {2, 80, "lew"}, {8, 50, "lew"}, {4, 45, "lee"}, {1, 90, "song"},\
							   {3, 45, "kim"}, {5, 50, "song"}, {9, 100, "lee"}, {7, 75, "moon"}, {6, 90, "park"}, \
							   {15, 90, "ki"}, {11, 20, "kong"}, {14, 40, "shin"}, {12, 50, "son"}, {17, 48, "lee"}, \
							   {20, 100, "min"}, {19, 80, "you"}, {13, 45, "song"}, {16, 54, "no"}, {18, 100, "yang"} };

void Make_Test_Data(int n)
{
	int i;

	for (i = 0; i < n; i++)
	{
		exam[i] = test[i];
	}
}

int Create_Data(SCORE* p)
{
	printf("\n사번을 입력하세요 => ");
	scanf("%d", &p->id);
	fflush(stdin);
	printf("이름을 입력하세요 => ");
	scanf("%s", p->name);
	fflush(stdin);
	printf("점수를 입력하세요 => ");
	scanf("%d", &p->jumsu);
	fflush(stdin);
	p->next = (SCORE*)0x0;
	p->prev = (SCORE*)0x0;

	return 1;
}

int Print_All_Data(void)
{
	int i;

	printf("Head= 0x%.8X, Head.next=0x%.8X, Head.prev=0x%.8X\n", &Head, Head.next, Head.prev);

	for (i = 0; i < MAX_ST; i++)
	{
		if (exam[i].id == 0) break;
		printf("[%d] addr=0x%.8X, ID=%d, NAME=%s, SCORE=%d, next=0x%.8X, prev=0x%.8X\n", i, &exam[i], exam[i].id, exam[i].name, exam[i].jumsu, exam[i].next, exam[i].prev);
	}

	return i;
}

int Print_Data(int no)
{
	if (exam[no].id == 0) return -1;
	printf("[%d] addr=0x%.8X, ID=%d, NAME=%s, SCORE=%d, next=0x%.8X, prev=0x%.8X\n", &exam[no], exam[no].id, exam[no].name, exam[no].jumsu, exam[no].next, exam[no].prev);
	return 1;
}

int Count_Data(void)
{
	int i;

	for (i = 0; i < MAX_ST; i++)
	{
		if (exam[i].id == 0) break;
	}

	return i;
}

int Insert_Data(SCORE* p)
{
	int i;

	for (i = 0; i < MAX_ST; i++)
	{
		if (exam[i].id == 0)
		{
			exam[i] = (*p);
			return i;
		}

		if (exam[i].id == p->id)
		{
			return -2;
		}
	}

	return -1;
}

int Print_All_Node(SCORE* head)
{
	int i;

	printf("Head.next = 0x%.8X Head.prev = 0x%.8X\n", head->next, head->prev);

	for (i = 0; i < MAX_ST; i++)
	{
		if (head->next == (SCORE*)0x0) return i;
		printf("addr = 0x%.8X, ID=%d, NAME=%s, SCORE=%d, next=0x%.8X, prev=0x%.8X\n", head->next, head->next->id, head->next->name, head->next->jumsu, head->next->next, head->next->prev);
		head = head->next;
	}
	return i;
}

int Count_Node(SCORE* head)
{
	int i;

	for (i = 0; i < MAX_ST; i++)
	{
		if (head->next == (SCORE*)0x0) return i;
		head = head->next;
	}
	return i;
}

SCORE* Search_Id_Node(SCORE* head, int id)
{
	for (;;)
	{
		if (head->next == (SCORE*)0x0) return (SCORE*)0x0;
		if (head->next->id == id) return head->next;
		head = head->next;
	}
}

int Print_Node(SCORE* head, int id)
{
	SCORE* p = Search_Id_Node(head, id);

	if (p != (SCORE*)0x0)
	{
		printf("ID=%d, NAME=%s, SCORE=%d, next=0x%.8X, prev=0x%.8X\n", p->id, p->name, p->jumsu, p->next, p->prev);
		return 1;
	}

	return -1;
}

int Copy_All_Node(SCORE* head, SCORE* buf)
{
	int i;
	if (head->next == NULL) return -1;

	for (i = 0; i < MAX_ST; i++)
	{
		if (head->next == NULL) break;
		buf[i] = *head->next;
		buf[i].next = &buf[i + 1];
		head = head->next;
	}

	buf[i - 1].next = NULL;
	return i;
}

int Count_Name_Node(SCORE* head, char* name)
{
	int n = 0;

	if (head->next == (SCORE*)0x0) return 0;
	head = head->next;

	for (;;)
	{
		if (!strcmp(head->name, name)) n++;
		if (head->next == (SCORE*)0x0) return n;
		head = head->next;
	}
}

int Count_Score_Node(SCORE* head, int jumsu)
{
	int n = 0;

	if (head->next == (SCORE*)0x0) return 0;
	head = head->next;

	for (;;)
	{
		if (head->jumsu == jumsu) n++;
		if (head->next == (SCORE*)0x0) return n;
		head = head->next;
	}
}

int Copy_Name_Node(SCORE* head, char* name, SCORE* buf)
{
	int n = 0;

	if (head->next == (SCORE*)0x0) return 0;
	head = head->next;

	for (;;)
	{
		if (!strcmp(head->name, name))
		{
			buf[n] = *head;
			buf[n].next = &buf[n + 1];
			n++;
		}
		if (head->next == (SCORE*)0x0) break;
		head = head->next;
	}
	buf[n - 1].next = (SCORE*)0x0;
	return n;
}

int Copy_Score_Node(SCORE* head, int jumsu, SCORE* buf)
{
	int n = 0;

	if (head->next == (SCORE*)0x0) return 0;
	head = head->next;

	for (;;)
	{
		if (head->jumsu == jumsu)
		{
			buf[n] = *head;
			buf[n].next = &buf[n + 1];
			n++;
		}
		if (head->next == (SCORE*)0x0) break;
		head = head->next;
	}
	buf[n - 1].next = (SCORE*)0x0;
	return n;
}

#endif

/***********************************************************/
// [1-4-2.2] 데이터 하나를 생성하여 Linked List에 추가하는 함수
/***********************************************************/

#if 0

int Insert_Node(SCORE* head, SCORE* d)
{
	SCORE* prev = head;

	while (prev->next) {
		if (prev->next->id > d->id) break;
		if (prev->next->id == d->id) return -2;
		prev = prev->next;
	}
	d->prev = prev;
	d->next = prev->next;

	d->prev->next = d;
	if(d->next) d->next->prev = d;

	return 1;
}

#endif

#if 0

void main(void)
{
	int i;
	int r;

	for (i = 0; i < 8; i++)
	{
		printf("[Loop: %d] Insert Result = %d\n", i, r = Insert_Data(&test[i]));
		printf("Printed Data Count = %d\n", Print_All_Data());
		printf("Insert Node Result = %d\n", Insert_Node(&Head, &exam[r]));
		printf("Printed Data Count = %d\n", Print_All_Data());
	}
}

#endif

/***********************************************************/
// [1-4-2.3] 주어진 사번의 node를 찾아서 삭제하는 함수
/***********************************************************/

#if 0

int Delete_Node(SCORE* head, int id)
{
	SCORE* delnode = Search_Id_Node(head, id);
	if (delnode == (SCORE*)0) return -1;

	delnode->prev->next = delnode->next;
	if(delnode->next) delnode->next->prev = delnode->prev;
	delnode->id = 0;

	return 1;
}

#endif

#if 0

void main(void)
{
	int i;
	int r;

	for (i = 0; i < 8; i++)
	{
		printf("[Loop: %d] Insert Result = %d\n", i, r = Insert_Data(&test[i]));
		printf("Insert Node Result = %d\n", Insert_Node(&Head, &exam[r]));
	}

	printf("Printed Node Count = %d\n", Print_All_Node(&Head));
	printf("[8] Delete Node Result = %d\n", Delete_Node(&Head, 8));
	printf("Printed Node Count = %d\n", Print_All_Node(&Head));
	printf("[7] Delete Node Result = %d\n", Delete_Node(&Head, 7));
	printf("Printed Node Count = %d\n", Print_All_Node(&Head));
	printf("[1] Delete Node Result = %d\n", Delete_Node(&Head, 1));
	printf("Printed Node Count = %d\n", Print_All_Node(&Head));
	printf("[10] Delete Node Result = %d\n", Delete_Node(&Head, 10));
	printf("Printed Node Count = %d\n", Print_All_Node(&Head));
}

#endif

/***********************************************************/
// [1-4-2.4] 더블 링크 사용의 장점 1. 내림차순 검색
/***********************************************************/

#if 0

int Print_All_Node_Reverse(SCORE* head)
{
	SCORE* node = head;
	// SCORE* node = head->next;
	// if (node == (SCORE*)0) return 0;
	while (node->next) node = node->next;

	while (node != head) {
		printf("addr=0x%.8X, ID=%d, NAME=%s, SCORE=%d\n", node, node->id, node->name, node->jumsu);
		node = node->prev;
	}
	return 1;
}

#endif

#if 0

void main(void)
{
	int i;
	int r;

	for (i = 0; i < 8; i++)
	{
		printf("[Loop: %d] Insert Result = %d\n", i, r = Insert_Data(&test[i]));
		printf("Insert Node Result = %d\n", Insert_Node(&Head, &exam[r]));
	}

	printf("Printed Node Count(Up) = %d\n", Print_All_Node(&Head));
	printf("Printed Node Count(Down) = %d\n", Print_All_Node_Reverse(&Head));
	printf("[8] Delete Node Result = %d\n", Delete_Node(&Head, 8));
	printf("Printed Node Count(Down) = %d\n", Print_All_Node_Reverse(&Head));
}

#endif

/***********************************************************/
// [1-4-2.5] 더블 링크 사용의 장점 2. 역방향으로 일정 범위 인쇄
/***********************************************************/

#if 0

int Print_Selected_Node(SCORE* head, int id, int num)
{
	int i = 0;

	head = Search_Id_Node(head, id);

	if (head == (SCORE*)0x0) return -1;

	printf("==================================================================================\n");

	while (i < num)
	{
		printf("addr = 0x%.8X, ID=%d, NAME=%s, SCORE=%d, next=0x%.8X, prev=0x%.8X\n", head, head->id, head->name, head->jumsu, head->next, head->prev);
		i++;
		if (head->next == (SCORE*)0x0) break;
		head = head->next;
	}

	return i;
}

int Print_Selected_Node_Reverse(SCORE* head, int id, int num)
{
	int i = 0;

	head = Search_Id_Node(head, id);

	if (head == (SCORE*)0x0) return -1;

	printf("==================================================================================\n");

	while (i < num)
	{
		printf("addr = 0x%.8X, ID=%d, NAME=%s, SCORE=%d, next=0x%.8X, prev=0x%.8X\n", head, head->id, head->name, head->jumsu, head->next, head->prev);
		i++;
		if (head->prev->prev == (SCORE*)0x0) break;
		head = head->prev;
	}

	return i;
}

#endif

#if 0

void main(void)
{
	int i;
	int r;

	for (i = 0; i < MAX_ST; i++)
	{
		printf("[Loop: %d] Insert Result = %d\n", i, r = Insert_Data(&test[i]));
		printf("Insert Node Result = %d\n", Insert_Node(&Head, &exam[r]));
	}

	printf("Printed Node Count(Up) = %d\n", Print_All_Node(&Head));
	printf("Printed Node Count(Down) = %d\n", Print_All_Node_Reverse(&Head));

	r = Print_Selected_Node(&Head, 7, 3);
	printf("Printed Data Number => %d\n", r);

	r = Print_Selected_Node(&Head, 19, 3);
	printf("Printed Data Number => %d\n", r);

	r = Print_Selected_Node_Reverse(&Head, 7, 3);
	printf("Printed Data Number => %d\n", r);

	r = Print_Selected_Node_Reverse(&Head, 2, 3);
	printf("Printed Data Number => %d\n", r);
}

#endif

#endif

/***********************************************************/
// [1-4-3] Heap 기반 연결 리스트
/***********************************************************/
#if 0

#if 0

/***********************************************************/
// [1-4-3.1] 전달받은 데이터를 힙에 생성하고 linked list에 추가하는 함수
/***********************************************************/

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <malloc.h>

typedef struct _score
{
	int id;
	int jumsu;
	char name[10];
	struct _score* next;
}SCORE;

SCORE Head;

// 이제부터 설계되는 모든 함수는 이 부분에 선언을 추가한다.

int Print_All_Data(void);
int Print_Data(int no);
int Count_Data(void);
int Create_Data(SCORE* p);
// int Insert_Data(SCORE* p);
int Insert_Node(SCORE* head, SCORE* d);
int Print_All_Node(SCORE* head);
SCORE* Search_Id_Node(SCORE* head, int id);
int Count_Node(SCORE* head);
int Print_Node(SCORE* head, int id);
int Delete_Node(SCORE* head, int id);
int Copy_All_Node(SCORE* head, SCORE* buf);
int Count_Name_Node(SCORE* head, char* name);
int Count_Score_Node(SCORE* head, int jumsu);
int Copy_Name_Node(SCORE* head, char* name, SCORE* buf);
int Copy_Score_Node(SCORE* head, int jumsu, SCORE* buf);

#define MAX_ST  20

SCORE test[MAX_ST] = { {10, 50, "kim"}, {2, 80, "lew"}, {8, 50, "lew"}, {4, 45, "lee"}, {1, 90, "song"},\
							   {3, 45, "kim"}, {5, 50, "song"}, {9, 100, "lee"}, {7, 75, "moon"}, {6, 90, "park"}, \
							   {15, 90, "ki"}, {11, 20, "kong"}, {14, 40, "shin"}, {12, 50, "son"}, {17, 48, "lee"}, \
							   {20, 100, "min"}, {19, 80, "you"}, {13, 45, "song"}, {16, 54, "no"}, {18, 100, "yang"} };

int Create_Data(SCORE* p)
{
	printf("\n사번을 입력하세요 => ");
	scanf("%d", &p->id);
	fflush(stdin);
	printf("이름을 입력하세요 => ");
	scanf("%s", p->name);
	fflush(stdin);
	printf("점수를 입력하세요 => ");
	scanf("%d", &p->jumsu);
	fflush(stdin);
	p->next = (SCORE*)0x0;

	return 1;
}

int Print_All_Node(SCORE* head)
{
	int n = 0;

	printf("Head.next = 0x%.8X\n", head->next);
	if (head->next == (SCORE*)0x0) return 0;
	head = head->next;

	for (;;)
	{
		printf("addr = 0x%.8X, ID=%d, NAME=%s, SCORE=%d, next = 0x%.8X\n", head, head->id, head->name, head->jumsu, head->next);
		n++;
		if (head->next == (SCORE*)0x0) return n;
		head = head->next;
	}
}

SCORE* Search_Id_Node(SCORE* head, int id)
{
	if (head->next == (SCORE*)0x0) return (SCORE*)0x0;
	head = head->next;

	for (;;)
	{
		if (head->id == id) return head;
		if (head->next == (SCORE*)0x0) return (SCORE*)0x0;
		head = head->next;
	}
}

int Count_Node(SCORE* head)
{
	int n = 0;

	if (head->next == (SCORE*)0x0) return 0;
	head = head->next;

	for (;;)
	{
		n++;
		if (head->next == (SCORE*)0x0) return n;
		head = head->next;
	}
}

int Print_Node(SCORE* head, int id)
{
	SCORE* p = Search_Id_Node(head, id);

	if (p != (SCORE*)0x0)
	{
		printf("ID=%d, NAME=%s, SCORE=%d, next = 0x%.8X\n", p->id, p->name, p->jumsu, p->next);
		return 1;
	}

	return -1;
}

int Copy_All_Node(SCORE* head, SCORE* buf)
{
	int n = 0;

	if (head->next == (SCORE*)0x0) return -1;
	head = head->next;

	for (;;)
	{
		buf[n] = *head;
		buf[n].next = &buf[n + 1];
		if (head->next == (SCORE*)0x0)
		{
			buf[n].next = (SCORE*)0x0;
			return n + 1;
		}
		n++;
		head = head->next;
	}
}

int Count_Name_Node(SCORE* head, char* name)
{
	int n = 0;

	if (head->next == (SCORE*)0x0) return 0;
	head = head->next;

	for (;;)
	{
		if (!strcmp(head->name, name)) n++;
		if (head->next == (SCORE*)0x0) return n;
		head = head->next;
	}
}

int Count_Score_Node(SCORE* head, int jumsu)
{
	int n = 0;

	if (head->next == (SCORE*)0x0) return 0;
	head = head->next;

	for (;;)
	{
		if (head->jumsu == jumsu) n++;
		if (head->next == (SCORE*)0x0) return n;
		head = head->next;
	}
}

int Copy_Name_Node(SCORE* head, char* name, SCORE* buf)
{
	int n = 0;

	if (head->next == (SCORE*)0x0) return 0;
	head = head->next;

	for (;;)
	{
		if (!strcmp(head->name, name))
		{
			buf[n] = *head;
			buf[n].next = &buf[n + 1];
			n++;
		}

		if (head->next == (SCORE*)0x0)
		{
			buf[n - 1].next = (SCORE*)0x0;
			return n;
		}

		head = head->next;
	}
}

int Copy_Score_Node(SCORE* head, int jumsu, SCORE* buf)
{
	int n = 0;

	if (head->next == (SCORE*)0x0) return 0;
	head = head->next;

	for (;;)
	{
		if (head->jumsu == jumsu)
		{
			buf[n] = *head;
			buf[n].next = &buf[n + 1];
			n++;
		}

		if (head->next == (SCORE*)0x0)
		{
			buf[n - 1].next = (SCORE*)0x0;
			return n;
		}

		head = head->next;
	}
}
#endif
/***********************************************************/
// [1-4-3.2] 전달받은 데이터를 힙에 생성하고 Linked List에 추가하는 함수 (calloc 사용)
/***********************************************************/

#if 0

int Insert_Node(SCORE* head, SCORE* d)
{
	SCORE* node = head;
	SCORE* newnode;
	while (node->next) {
		if (node->next->id > d->id) break;
		else if (node->next->id == d->id) return -2;
		node = node->next;
	}

	newnode = (SCORE*)calloc(1, sizeof(SCORE));
	if (newnode == (SCORE*)0) return -1;
	*newnode = *d;

	newnode->next = node->next;
	node->next = newnode;
	return 1;
}

#endif

#if 0

void main(void)
{
	int i;
	SCORE* p;

	for (i = 0; i < 8; i++)
	{
		printf("Insert Node Result = %d\n", Insert_Node(&Head, &test[i]));
	}

	printf("Printed Node Count = %d\n", Print_All_Node(&Head));

	printf("Searched Node Address = 0x%.8X\n", p = Search_Id_Node(&Head, 8));

	if (p != (SCORE*)0x0)
	{
		printf("ID=%d, NAME=%s, SCORE=%d, next = 0x%.8X\n", p->id, p->name, p->jumsu, p->next);
	}

	printf("Searched Node Address = 0x%.8X\n", p = Search_Id_Node(&Head, 7));

	if (p != (SCORE*)0x0)
	{
		printf("ID=%d, NAME=%s, SCORE=%d, next = 0x%.8X\n", p->id, p->name, p->jumsu, p->next);
	}
}

#endif

/***********************************************************/
// [1-4-3.3] 전달받은 사번의 자료를 링크와 힙에서 삭제하는 함수 (free 사용)
/***********************************************************/

#if 0

int Delete_Node(SCORE* head, int id)
{
	SCORE* node = head;
	while (node->next) {
		if (node->next->id == id) {
			SCORE* delnode = node->next;
			node->next = node->next->next;
			free(delnode);
			return 1;
		}
		node = node->next;
	}
	return -1;
}

#endif

#if 0

void main(void)
{
	int i;

	for (i = 0; i < 8; i++)
	{
		printf("Insert Node Result = %d\n", Insert_Node(&Head, &test[i]));
	}

	printf("Printed Node Count = %d\n", Print_All_Node(&Head));
	printf("Delete Node Result = %d\n", Delete_Node(&Head, 8));
	printf("Delete Node Result = %d\n", Delete_Node(&Head, 7));
	printf("Delete Node Result = %d\n", Delete_Node(&Head, 1));
	printf("Delete Node Result = %d\n", Delete_Node(&Head, 10));
	printf("Printed Node Count = %d\n", Print_All_Node(&Head));
}

#endif

#endif


/***********************************************************/
// [1-4-4] �� ��� ���� ����Ʈ - ���� ��ũ
/***********************************************************/

#if 0

/***********************************************************/
// [1-4-4.0] ���� Linked List ����� �״�� ����ϴ� �Լ���
/***********************************************************/

#if 0

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <malloc.h>

typedef struct _score
{
	int id;
	int jumsu;
	char name[10];
	struct _score* next;
	struct _score* prev;
}SCORE;

SCORE Head;

#define MAX_ST		20

int Print_All_Data(void);
int Print_Data(int no);
int Count_Data(void);
int Create_Data(SCORE* p);
int Insert_Data(SCORE* p);
int Insert_Node(SCORE* head, SCORE* d);
int Print_All_Node(SCORE* head);
int Print_All_Node_Reverse(SCORE* head);
SCORE* Search_Id_Node(SCORE* head, int id);
int Count_Node(SCORE* head);
int Print_Node(SCORE* head, int id);
int Delete_Node(SCORE* head, int id);
int Copy_All_Node(SCORE* head, SCORE* buf);
int Count_Name_Node(SCORE* head, char* name);
int Count_Score_Node(SCORE* head, int jumsu);
int Copy_Name_Node(SCORE* head, char* name, SCORE* buf);
int Copy_Score_Node(SCORE* head, int jumsu, SCORE* buf);
int Print_Selected_Node(SCORE* head, int id, int num);
int Print_Selected_Node_Reverse(SCORE* head, int id, int num);

SCORE test[MAX_ST] = { {10, 50, "kim"}, {2, 80, "lew"}, {8, 50, "lew"}, {4, 45, "lee"}, {1, 90, "song"},\
							   {3, 45, "kim"}, {5, 50, "song"}, {9, 100, "lee"}, {7, 75, "moon"}, {6, 90, "park"}, \
							   {15, 90, "ki"}, {11, 20, "kong"}, {14, 40, "shin"}, {12, 50, "son"}, {17, 48, "lee"}, \
							   {20, 100, "min"}, {19, 80, "you"}, {13, 45, "song"}, {16, 54, "no"}, {18, 100, "yang"} };


int Create_Data(SCORE* p)
{
	printf("\n사번을 입력하세요 => ");
	scanf("%d", &p->id);
	fflush(stdin);
	printf("이름을 입력하세요=> ");
	scanf("%s", p->name);
	fflush(stdin);
	printf("점수를 입력하세요 => ");
	scanf("%d", &p->jumsu);
	fflush(stdin);
	p->next = (SCORE*)0x0;
	p->prev = (SCORE*)0x0;

	return 1;
}

SCORE* Search_Id_Node(SCORE* head, int id)
{
	for (;;)
	{
		if (head->next == (SCORE*)0x0) return (SCORE*)0x0;
		if (head->next->id == id) return head->next;
		head = head->next;
	}
}

int Count_Node(SCORE* head)
{
	int i = 0;

	for (;;)
	{
		if (head->next == (SCORE*)0x0) return i;
		head = head->next;
		i++;
	}
}

int Print_Node(SCORE* head, int id)
{
	SCORE* p = Search_Id_Node(head, id);

	if (p != (SCORE*)0x0)
	{
		printf("ID=%d, NAME=%s, SCORE=%d, next=0x%.8X, prev=0x%.8X\n", p->id, p->name, p->jumsu, p->next, p->prev);
		return 1;
	}

	return -1;
}

int Copy_All_Node(SCORE* head, SCORE* buf)
{
	int i = 0;
	if (head->next == NULL) return -1;

	for (;;)
	{
		if (head->next == NULL) break;
		buf[i] = *head->next;
		buf[i].next = &buf[i + 1];
		head = head->next;
		i++;
	}

	buf[i - 1].next = NULL;
	return i;
}

int Count_Name_Node(SCORE* head, char* name)
{
	int n = 0;

	if (head->next == (SCORE*)0x0) return 0;
	head = head->next;

	for (;;)
	{
		if (!strcmp(head->name, name)) n++;
		if (head->next == (SCORE*)0x0) return n;
		head = head->next;
	}
}

int Count_Score_Node(SCORE* head, int jumsu)
{
	int n = 0;

	if (head->next == (SCORE*)0x0) return 0;
	head = head->next;

	for (;;)
	{
		if (head->jumsu == jumsu) n++;
		if (head->next == (SCORE*)0x0) return n;
		head = head->next;
	}
}

int Copy_Name_Node(SCORE* head, char* name, SCORE* buf)
{
	int n = 0;

	if (head->next == (SCORE*)0x0) return 0;
	head = head->next;

	for (;;)
	{
		if (!strcmp(head->name, name))
		{
			buf[n] = *head;
			buf[n].next = &buf[n + 1];
			n++;
		}
		if (head->next == (SCORE*)0x0) break;
		head = head->next;
	}
	buf[n - 1].next = (SCORE*)0x0;
	return n;
}

int Copy_Score_Node(SCORE* head, int jumsu, SCORE* buf)
{
	int n = 0;

	if (head->next == (SCORE*)0x0) return 0;
	head = head->next;

	for (;;)
	{
		if (head->jumsu == jumsu)
		{
			buf[n] = *head;
			buf[n].next = &buf[n + 1];
			n++;
		}
		if (head->next == (SCORE*)0x0) break;
		head = head->next;
	}
	buf[n - 1].next = (SCORE*)0x0;
	return n;
}

int Print_All_Node(SCORE* head)
{
	int i = 0;

	printf("Head.next = 0x%.8X Head.prev = 0x%.8X\n", head->next, head->prev);

	for (;;)
	{
		if (head->next == (SCORE*)0x0) return i;
		printf("addr = 0x%.8X, ID=%d, NAME=%s, SCORE=%d, next=0x%.8X, prev=0x%.8X\n", head->next, head->next->id, head->next->name, head->next->jumsu, head->next->next, head->next->prev);
		head = head->next;
		i++;
	}
}

int Print_All_Node_Reverse(SCORE* head)
{
	int i = 0;

	printf("Head.next = 0x%.8X Head.prev = 0x%.8X\n", head->next, head->prev);

	while (head->next != (SCORE*)0x0)
	{
		head = head->next;
	}

	printf("Tail.next = 0x%.8X Tail.prev = 0x%.8X\n", head->next, head->prev);

	for (;;)
	{
		if (head->prev == (SCORE*)0x0) return i;
		printf("addr = 0x%.8X, ID=%d, NAME=%s, SCORE=%d, next=0x%.8X, prev=0x%.8X\n", head, head->id, head->name, head->jumsu, head->next, head->prev);
		head = head->prev;
		i++;
	}
}

int Print_Selected_Node(SCORE* head, int id, int num)
{
	int i = 0;

	head = Search_Id_Node(head, id);

	if (head == (SCORE*)0x0) return -1;

	printf("==================================================================================\n");

	while (i < num)
	{
		printf("addr = 0x%.8X, ID=%d, NAME=%s, SCORE=%d, next=0x%.8X, prev=0x%.8X\n", head, head->id, head->name, head->jumsu, head->next, head->prev);
		i++;
		if (head->next == (SCORE*)0x0) break;
		head = head->next;
	}

	return i;
}

int Print_Selected_Node_Reverse(SCORE* head, int id, int num)
{
	int i = 0;

	head = Search_Id_Node(head, id);

	if (head == (SCORE*)0x0) return -1;

	printf("==================================================================================\n");

	while (i < num)
	{
		printf("addr = 0x%.8X, ID=%d, NAME=%s, SCORE=%d, next=0x%.8X, prev=0x%.8X\n", head, head->id, head->name, head->jumsu, head->next, head->prev);
		i++;
		if (head->prev->prev == (SCORE*)0x0) break;
		head = head->prev;
	}

	return i;
}

#endif

/***********************************************************/
// [1-4-4.1] 데이터 하나를 생성하여 linked List에 추가하는 함수 (calloc 사용)
/***********************************************************/

#if 0

int Insert_Node(SCORE* head, SCORE* d)
{
	SCORE* node = head;
	SCORE* newnode;
	while (node->next) {
		if (node->next->id > d->id) break;
		if (node->next->id == d->id) return -2;
		node = node->next;
	}

	newnode = (SCORE*)calloc(1, sizeof(SCORE));
	if (newnode == (SCORE*)0) return -1;

	*newnode = *d;
	newnode->prev = node;
	newnode->next = node->next;

	newnode->prev->next = newnode;
	if (newnode->next) newnode->next->prev = newnode;

	return 1;
}

#endif

#if 0

void main(void)
{
	int i;

	for (i = 0; i < 8; i++)
	{
		printf("Insert Node Result = %d\n", Insert_Node(&Head, &test[i]));
		printf("Printed Node Count = %d\n", Print_All_Node(&Head));
	}
}

#endif

/***********************************************************/
// [1-4-4.2] 주어진 사번의 node를 찾아서 삭제하는 함수
/***********************************************************/

#if 0

int Delete_Node(SCORE* head, int id)
{
	SCORE* delnode = Search_Id_Node(head, id);
	if (delnode == (SCORE*)0) return -1;
			
	delnode->prev->next = delnode->next;
	if (delnode->next) delnode->next->prev = delnode->prev;
	free(delnode);
	return 1;
}

#endif

#if 0

void main(void)
{
	int i;

	for (i = 0; i < 8; i++)
	{
		printf("Insert Node Result = %d\n", Insert_Node(&Head, &test[i]));
	}

	printf("Printed Node Count = %d\n", Print_All_Node(&Head));
	printf("Delete Node Result = %d\n", Delete_Node(&Head, 8));
	printf("Printed Node Count = %d\n", Print_All_Node(&Head));
	printf("Delete Node Result = %d\n", Delete_Node(&Head, 7));
	printf("Printed Node Count = %d\n", Print_All_Node(&Head));
	printf("Delete Node Result = %d\n", Delete_Node(&Head, 1));
	printf("Printed Node Count = %d\n", Print_All_Node(&Head));
	printf("Delete Node Result = %d\n", Delete_Node(&Head, 10));
	printf("Printed Node Count = %d\n", Print_All_Node(&Head));
}

#endif

#endif


/***********************************************************/
// [1-5] 연결리스트 기반 스택과 큐
/***********************************************************/

/***********************************************************/
// [1-5-1] 힙 기반 stack
/***********************************************************/

#if 0

#include <stdio.h>
#include <malloc.h>

typedef struct _stk
{
	int num;
	struct _stk* next;
}STACK;

int cnt_data; // data 개수 관리
STACK* Sptr = (STACK*)0;
STACK a[10] = { {1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0},{8,0},{9,0},{10,0} };

int Push_Stack(STACK* data);
int Pop_Stack(STACK* p);
int Print_Stack(void);
int Count_Full_Data_Stack(void);

int Push_Stack(STACK* data)
{
	STACK* newnode = (STACK*)calloc(1, sizeof(STACK));
	if (newnode == (STACK*)0) return -1;

	*newnode = *data;
	newnode->next = Sptr; // stack pointer가 가르키던 데이터가 newnode의 다음 노드
	Sptr = newnode; // stack pointer는 newnode가 된다.
	cnt_data++;

	return 1;
}

int Pop_Stack(STACK* p) // pop한 data를 넣을 메모리 주소를 인자로 넣어준다.
{
	STACK *delnode;
	if (Sptr == (STACK*)0) return -1;

	*p = *Sptr;

	delnode = Sptr;
	Sptr = Sptr->next;
	cnt_data--;

	free(delnode);
	return 1;
}

int Print_Stack(void)
{
	//int cnt = 0;
	STACK* node = Sptr;
	while (node) {
		printf("%d ", node->num);
		//cnt++;
		node = node->next;
	}
	printf("\n");
	return cnt_data;
	//return cnt;
}

int Count_Full_Data_Stack(void)
{
	/*int cnt = 0;
	STACK* node = Sptr;
	while (node) {
		cnt++;
		node = node->next;
	}

	return cnt;*/
	return cnt_data;
}

void main(void)
{
	int i;

	for (i = 0; i < 5; i++)
	{
		printf("Push Result = %d\n", Push_Stack(&a[i]));
		printf("Print Result = %d, ", Print_Stack());
		printf("Full = %d\n", Count_Full_Data_Stack());
	}

	for (i = 0; i < 6; i++)
	{
		printf("Pop Result = %d\n", Pop_Stack(&a[i]));
		printf("Print Result = %d, ", Print_Stack());
		printf("Full = %d\n ", Count_Full_Data_Stack());
	}

	for (i = 0; i < 3; i++)
	{
		printf("Push Result = %d\n", Push_Stack(&a[i]));
		printf("Print Result = %d, ", Print_Stack());
		printf("Full = %d\n", Count_Full_Data_Stack());
	}

	for (i = 0; i < 5; i++)
	{
		printf("Pop Result = %d\n", Pop_Stack(&a[i]));
		printf("Print Result = %d, ", Print_Stack());
		printf("Full = %d\n ", Count_Full_Data_Stack());
	}

	printf("\n");
}

#endif

/***********************************************************/
// [1-5-2] 힙 기반 Linear Queue
/***********************************************************/
#if 0

#include <stdio.h>
#include <malloc.h>

typedef struct _que
{
	int num;
	struct _que* next;
}QUEUE;

int cnt_data;
QUEUE* Wrptr = (QUEUE*)0;;
QUEUE* Rdptr = (QUEUE*)0;;

QUEUE a[10] = { {1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0},{8,0},{9,0},{10,0} };

int In_Queue(QUEUE* data);
int Out_Queue(QUEUE* p);
int Print_Queue(void);
int Count_Full_Data_Queue(void);

int In_Queue(QUEUE* data)
{
	QUEUE* newnode = (QUEUE*)calloc(1, sizeof(QUEUE));
	if (newnode == (QUEUE*)0) return -1;

	*newnode = *data;
	newnode->next = (QUEUE*)0;
	
	if (Wrptr == (QUEUE*)0) {
		Wrptr = Rdptr = newnode;
	}
	else {
		Wrptr->next = newnode;
		Wrptr = newnode;
	}
	cnt_data++;

	return 1;
}

int Out_Queue(QUEUE* p)
{
	if (Rdptr == (QUEUE*)0) return -1;
	
	*p = *Rdptr;

	QUEUE* delnode;
	delnode = Rdptr;
	Rdptr = Rdptr->next;

	cnt_data--;
	free(delnode);

	if (Rdptr == (QUEUE*)0) Wrptr = (QUEUE*)0;
	return 1;
}

int Print_Queue(void)
{
	int cnt = 0;
	QUEUE* node = Rdptr;
	while (node) {
		printf("%d ", node->num);
		//cnt++;
		node = node->next;
	}
	printf("\n");
	return cnt_data;
	//return cnt;
}

int Count_Full_Data_Queue(void)
{
	/*int cnt = 0;
	QUEUE* node = Rdtr;
	while (node) {
		cnt++;
		node = node->next;
	}

	return cnt;*/
	return cnt_data;
}

void main(void)
{
	int i;

	for (i = 0; i < 3; i++)
	{
		printf("Queue Result = %d\n", In_Queue(&a[i]));
		printf("Print Result = %d, ", Print_Queue());
		printf("Full = %d\n", Count_Full_Data_Queue());
	}

	for (i = 0; i < 2; i++)
	{
		printf("Dequeue Result = %d\n", Out_Queue(&a[i]));
		printf("Print Result = %d, ", Print_Queue());
		printf("Full = %d\n", Count_Full_Data_Queue());
	}

	for (i = 0; i < 4; i++)
	{
		printf("Queue Result = %d\n", In_Queue(&a[i]));
		printf("Print Result = %d, ", Print_Queue());
		printf("Full = %d\n", Count_Full_Data_Queue());
	}

	for (i = 0; i < 7; i++)
	{
		printf("Dequeue Result = %d\n", Out_Queue(&a[i]));
		printf("Print Result = %d, ", Print_Queue());
		printf("Full = %d\n", Count_Full_Data_Queue());
	}

	for (i = 0; i < 3; i++)
	{
		printf("Queue Result = %d\n", In_Queue(&a[i]));
		printf("Print Result = %d, ", Print_Queue());
		printf("Full = %d\n", Count_Full_Data_Queue());
	}

	for (i = 0; i < 3; i++)
	{
		printf("Dequeue Result = %d\n", Out_Queue(&a[i]));
		printf("Print Result = %d, ", Print_Queue());
		printf("Full = %d\n", Count_Full_Data_Queue());
	}
}

#endif


/***********************************************************/
// [2-1] 비선형 자료구조
/***********************************************************/

#if 0
#include <stdio.h>
#include <stdlib.h>

/***********************************************************/
// [2-1.1] Graph 기본 자료
/***********************************************************/

#define NUM_NODE 6 // 정점의 개수
#define NUM_EDGE 16 // 간선의 개수

typedef struct
{
	int s;
	int e;
	int cost;
}EDGE;
EDGE edge[16] = { {1,2,3},{1,4,6},{1,5,12},{2,3,2},{2,4,9},{3,2,4},{3,5,6},{3,6,7},{4,1,8},{4,5,5},{5,2,11},{5,3,8},{5,4,7},{5,6,5},{6,2,13},{6,3,5} };
// 간선 정보를 저장

/***********************************************************/
// [2-1.2] 인접 행렬
/***********************************************************/

#if 0

#define NOT_CONNECTED	(0x7fffffff)
int matrix[NUM_NODE + 1][NUM_NODE + 1];

void Init_Graph_Adjacency_Matrix(void)
{
	for (int i = 0; i <= NUM_NODE; i++) {
		for (int j = 0; j <= NUM_NODE; j++) {
			matrix[i][j] = NOT_CONNECTED;
		}
	}
	for (int i = 0; i < NUM_EDGE; i++) {
		matrix[edge[i].s][edge[i].e] = edge[i].cost;
	}
}


int visited[100];
int path_cnt;
int path[100];
void DFS(int cur, int e, int sum_cost)
{
	int i;
	visited[cur] = 1;
	path[path_cnt++] = cur;

	if (cur == e)
	{
		printf("%d ", path[0]);
		for (i = 1; i < path_cnt; i++) printf("- %d ", path[i]);
		printf("[total cost : %d]\n", sum_cost);
		visited[cur] = 0;
		path_cnt--;
		return;
	}

	for (i = 1; i <= NUM_NODE; i++)
	{
		if (matrix[cur][i] != NOT_CONNECTED && !visited[i])
		{
			DFS(i, e, sum_cost + matrix[cur][i]);
		}
	}

	visited[cur] = 0;
	path_cnt--;
}

int main(void)
{
	printf("Graph - Adjacency matrix\n\n");

	Init_Graph_Adjacency_Matrix();

	printf("[Path] Node 1 -> Node 6\n");
	DFS(1, 6, 0);

	printf("\n[Path] Node 3 -> Node 5\n");
	DFS(3, 5, 0);
}
#endif

/***********************************************************/
// [2-1.3] 인접 리스트 (배열 기반)
/***********************************************************/

#if 0
typedef struct list
{
	int node;
	int cost;
}LIST;

LIST list[NUM_NODE + 1][NUM_NODE];
int list_cnt[NUM_NODE + 1];

void Init_Graph_Adjacency_list(void)
{
	for (int i = 0; i < NUM_EDGE; i++) {
		list[edge[i].s][list_cnt[edge[i].s]].node = edge[i].e;
		list[edge[i].s][list_cnt[edge[i].s]].cost = edge[i].cost;
		list_cnt[edge[i].s]++;
	}
}

int visited[100];
int path_cnt;
int path[100];
void DFS(int cur, int e, int sum_cost)
{
	int i;
	visited[cur] = 1;
	path[path_cnt++] = cur;

	if (cur == e)
	{
		printf("%d ", path[0]);
		for (i = 1; i < path_cnt; i++) printf("- %d ", path[i]);
		printf("[total cost : %d]\n", sum_cost);
		visited[cur] = 0;
		path_cnt--;
		return;
	}

	for (i = 0; i < list_cnt[cur]; i++)
	{
		if (!visited[list[cur][i].node])
		{
			DFS(list[cur][i].node, e, sum_cost + list[cur][i].cost);
		}
	}

	visited[cur] = 0;
	path_cnt--;
}

int main(void)
{
	printf("Graph - Adjacency list\n\n");

	Init_Graph_Adjacency_list();

	printf("[Path] Node 1 -> Node 6\n");
	DFS(1, 6, 0);

	printf("\n[Path] Node 3 -> Node 5\n");
	DFS(3, 5, 0);

	return 0;
}
#endif

/***********************************************************/
// [2-1.4] 인접 리스트 (Heap 기반)
/***********************************************************/

#if 0

typedef struct list
{
	int node;
	int cost;
	struct list* next;
}LIST;

LIST list[NUM_NODE + 1];

int Init_Graph_Adjacency_list(void)
{
	for (int i = 0; i <= NUM_NODE; i++) {
		list[i].next = (LIST*)0;
	}
	for (int i = 0; i < NUM_EDGE; i++) {
		LIST* newnode = (LIST*)calloc(1, sizeof(LIST));
		if (newnode == (LIST*)0) return -1;

		newnode->node = edge[i].e;
		newnode->cost = edge[i].cost;

		newnode->next = list[edge[i].s].next; // list[edge[i].s]가 head
		list[edge[i].s].next = newnode;
	}
}

int visited[100];
int path_cnt;
int path[100];
void DFS(int cur, int e, int sum_cost)
{
	int i;
	LIST* p;
	visited[cur] = 1;
	path[path_cnt++] = cur;

	if (cur == e)
	{
		printf("%d ", path[0]);
		for (i = 1; i < path_cnt; i++) printf("- %d ", path[i]);
		printf("[total cost : %d]\n", sum_cost);
		visited[cur] = 0;
		path_cnt--;
		return;
	}

	p = list[cur].next;
	while (p != (LIST*)0)
	{
		if (!visited[p->node])
		{
			DFS(p->node, e, sum_cost + p->cost);
		}
		p = p->next;
	}

	visited[cur] = 0;
	path_cnt--;
}

int main(void)
{
	int ret;

	printf("Graph - Adjacency list\n\n");

	ret = Init_Graph_Adjacency_list();
	if (!ret) return 0;

	printf("[Path] Node 1 -> Node 6\n");
	DFS(1, 6, 0);

	printf("\n[Path] Node 3 -> Node 5\n");
	DFS(3, 5, 0);

	return 0;
}
#endif

#endif

/***********************************************************/
// [2-2] Hash Table
/***********************************************************/

#if 0

/***********************************************************/
// [2-2.1] Hash Table과 자료 검색
/***********************************************************/

#if 0

#include <stdio.h>
#include <string.h>
#include <conio.h>

#include <malloc.h>

typedef struct _score
{
	int id;
	int jumsu;
	char name[10];
}SCORE;

#define MAX_ST		20
#define HASH_KEY	10
#define STEP		1

SCORE Hash_table[MAX_ST];

int Create_Data(SCORE* p);
int Get_Hash_Key(int id); // 해시값 구하는 함수
void Init_Hash_Table(void);
void Print_All_Data(void);
int Insert_Data(SCORE* d);
SCORE* Search_Data(int id);
int Delete_Data(int id);

SCORE test[MAX_ST + 2] = { {10, 50, "kim"}, {2, 80, "lew"}, {8, 50, "lew"}, {4, 45, "lee"}, {1, 90, "song"},\
							   {3, 45, "kim"}, {5, 50, "song"}, {9, 100, "lee"}, {7, 75, "moon"}, {6, 90, "park"}, \
							   {15, 90, "ki"}, {11, 20, "kong"}, {14, 40, "shin"}, {12, 50, "son"}, {17, 48, "lee"}, \
							   {20, 100, "min"}, {19, 80, "you"}, {13, 45, "song"}, {16, 54, "no"}, {18, 100, "yang"}, \
							   {21, 58, "seo"}, {23, 88, "oh"} };

int Create_Data(SCORE* p)
{
	printf("\n사번을 입력하세요 => ");
	scanf("%d", &p->id);
	fflush(stdin);
	printf("이름을 입력하세요 => ");
	scanf("%s", p->name);
	fflush(stdin);
	printf("점수를 입력하세요 => ");
	scanf("%d", &p->jumsu);
	fflush(stdin);

	return 1;
}

int Get_Hash_Key(int id)
{
	return id % HASH_KEY;
}

void Init_Hash_Table(void)
{
	int i;

	for (i = 0; i < MAX_ST; i++)
	{
		Hash_table[i].id = -1;
	}
}

#endif

#if 0

void Print_All_Data(void)
{
	int i;

	for (i = 0; i < MAX_ST; i++)
	{
		if (Hash_table[i].id != -1) printf("[%d] ID: %d, NAME: %s\n", i, Hash_table[i].id, Hash_table[i].name);
	}
}

#endif

/***********************************************************/
// [2-2.2] Insert => Open Address 방법
/***********************************************************/

#if 0

int Insert_Data(SCORE* d)
{
	int hash = Get_Hash_Key(d->id);
	int hash_org = hash;

	if (Search_Data(d->id) != (SCORE*)0) return -2; // 삭제를 염두하여 do 밖에서 구현

	do {
		if (Hash_table[hash].id == -1) {
			Hash_table[hash] = *d;
			return hash;
		}
		else {
			hash = (hash + STEP) % MAX_ST;
		}
	} while (hash != hash_org);

	return -1;
}

#endif

#if 0

void main(void)
{
	int i;
	int r;

	Init_Hash_Table();

	for (i = 0; i < (MAX_ST + 2); i++)
	{
		printf("[Loop: %d] Inserted Position=%d, ID=%d\n", i, r = Insert_Data(&test[i]), test[i].id);
		Print_All_Data();
	}
}

#endif

/***********************************************************/
// [2-2.3] Search
/***********************************************************/

#if 0

SCORE* Search_Data(int id)
{
	int hash = Get_Hash_Key(id);
	int hash_org = hash;
	do {
		if (Hash_table[hash].id == id) return &Hash_table[hash];
		else if (Hash_table[hash].id == -1) break; // 이 이후에도 들어가지 않았을 것임(삭제 구현하기 전에 가능)
		else hash = (hash + STEP) % MAX_ST;
	} while (hash != hash_org);
	
	return (SCORE*)0;
}

#endif

#if 0

void main(void)
{
	int i;
	int r;
	SCORE* p;

	Init_Hash_Table();

	for (i = 0; i < 15; i++)
	{
		printf("[Loop: %d] Inserted Position=%d, ID=%d\n", i, r = Insert_Data(&test[i]), test[i].id);
	}

	Print_All_Data();
	printf("Serch Result=0x%.8X\n", p = Search_Data(3));
	if (p) printf("ID=%d, NAME=%s\n", p->id, p->name);
	printf("Serch Result=0x%.8X\n", p = Search_Data(12));
	if (p) printf("ID=%d, NAME=%s\n", p->id, p->name);
	printf("Serch Result=0x%.8X\n", p = Search_Data(25));
	if (p) printf("ID=%d, NAME=%s\n", p->id, p->name);
}

#endif

/***********************************************************/
// [2-2.4] Delete 함수의 예
/***********************************************************/

#if 0

int Delete_Data(int id)
{
	SCORE* p;

	p = Search_Data(id);
	if (p == (SCORE*)0) return -1;
	p->id = -1; // -1로 하면 빈 방인지, 삭제된 방인지 몰라 Search가 제대로 작동하지 않는다.
	return 1;
}

#endif

/***********************************************************/
// [2-2.5] 삭제 노드 ID를 -2로 하도록 delete 함수 설계를 다시 진행한다.
// 삭제 전략이 달라지면서 Insert 전략도 수정되어야 한다.
// 새로운 Insert 함수가 설계되면 [3-3.2]에서 설계된 Insert_Data 함수는 삭제한다.
/***********************************************************/

#if 0

int Delete_Data(int id)
{
	SCORE* delnode = Search_Data(id);
	if (delnode == (SCORE*)0) return -1;
	delnode->id = -2;

	return 1;
}

int Insert_Data(SCORE* d)
{
	int pos;
	int key;

	if (Search_Data(d->id) != (SCORE*)0) return -1;

	pos = key = Get_Hash_Key(d->id);

	for (;;)
	{
		if ((Hash_table[pos].id == -1) || (Hash_table[pos].id == -2))
		{
			Hash_table[pos] = *d;
			return pos;
		}

		pos += STEP;
		if (pos == key) return -1;
		if (pos >= MAX_ST) pos = 0;
	}
}

void Print_All_Data(void)
{
	int i;

	for (i = 0; i < MAX_ST; i++)
	{
		if ((Hash_table[i].id != -1) && (Hash_table[i].id != -2)) printf("[%d] ID: %d, NAME: %s\n", i, Hash_table[i].id, Hash_table[i].name);
	}
}

#endif

#if 0

void main(void)
{
	int i;
	int r;

	Init_Hash_Table();

	for (i = 0; i < 15; i++)
	{
		printf("[Loop: %d] Inserted Position=%d, ID=%d\n", i, r = Insert_Data(&test[i]), test[i].id);
	}

	Print_All_Data();
	printf("[3] Delete Result=%d\n", r = Delete_Data(3));
	printf("[12] Delete Result=%d\n", r = Delete_Data(12));
	printf("[25] Delete Result=%d\n", r = Delete_Data(25));
	printf("[3] Delete Result=%d\n", r = Delete_Data(3));
	printf("[12] Delete Result=%d\n", r = Delete_Data(12));
	Print_All_Data();

	printf("Inserted Position=%d, ID=%d\n", r = Insert_Data(&test[13]), test[13].id);
	printf("Inserted Position=%d, ID=%d\n", r = Insert_Data(&test[5]), test[5].id);
	Print_All_Data();
}

#endif

#endif

/***********************************************************/
// [2-2.6] Hash Table => 해시 키 발생 함수의 수정
/***********************************************************/

#if 0

/***********************************************************/
// [2-2.6] Hash Table을 위한 기본 함수들
/***********************************************************/

#if 0

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <malloc.h>

typedef struct _score
{
	int id;
	int jumsu;
	char name[10];
}SCORE;

#define MAX_ST		20

#if 0
#define HASH_KEY	10
#define STEP		1
#else
#define HASH_KEY	7  // 가급적 소수
#define STEP		9  // 테이블의 요소수와 서로소 관계인 수
#endif

SCORE Hash_table[MAX_ST];

int Create_Data(SCORE* p);
int Get_Hash_Key(int id);
void Init_Hash_Table(void);
void Print_All_Data(void);
int Insert_Data(SCORE* d);
SCORE* Search_Data(int id);
int Delete_Data(int id);

SCORE test[MAX_ST + 2] = { {10, 50, "kim"}, {2, 80, "lew"}, {8, 50, "lew"}, {4, 45, "lee"}, {1, 90, "song"},\
							   {3, 45, "kim"}, {5, 50, "song"}, {9, 100, "lee"}, {7, 75, "moon"}, {6, 90, "park"}, \
							   {15, 90, "ki"}, {11, 20, "kong"}, {14, 40, "shin"}, {12, 50, "son"}, {17, 48, "lee"}, \
							   {20, 100, "min"}, {19, 80, "you"}, {13, 45, "song"}, {16, 54, "no"}, {18, 100, "yang"}, \
							   {21, 58, "seo"}, {23, 88, "oh"} };

int Create_Data(SCORE* p)
{
	printf("\n사번을 입력하세요 => ");
	scanf("%d", &p->id);
	fflush(stdin);
	printf("이름을 입력하세요 => ");
	scanf("%s", p->name);
	fflush(stdin);
	printf("점수를 입력하세요 => ");
	scanf("%d", &p->jumsu);
	fflush(stdin);

	return 1;
}

int Get_Hash_Key(int id)
{
	return id % HASH_KEY;
}

void Init_Hash_Table(void)
{
	int i;

	for (i = 0; i < MAX_ST; i++)
	{
		Hash_table[i].id = -1;
	}
}

void Print_All_Data(void)
{
	int i;

	for (i = 0; i < MAX_ST; i++)
	{
		if ((Hash_table[i].id != -1) && (Hash_table[i].id != -2)) printf("[%d] ID: %d, NAME: %s\n", i, Hash_table[i].id, Hash_table[i].name);
	}
}

int Delete_Data(int id)
{
	SCORE* p;

	p = Search_Data(id);
	if (p == (SCORE*)0) return -1;
	p->id = -2;
	return 1;
}

int Insert_Data(SCORE* d)
{
	int pos;
	int cnt = 0;
	static int insert_cnt;

	pos = Get_Hash_Key(d->id);

	for (;;)
	{
		if ((Hash_table[pos].id == -1) || (Hash_table[pos].id == -2))
		{
			Hash_table[pos] = *d;
			insert_cnt += cnt + 1;
			printf("cnt = %d, total insert count = %d\n", cnt + 1, insert_cnt);
			return pos;
		}

		pos += STEP;
		cnt++;
		if (cnt >= MAX_ST) return -1;
		if (pos >= MAX_ST) pos %= MAX_ST;
	}
}

SCORE* Search_Data(int id)
{
	int pos;
	int cnt = 0;
	static int search_cnt;

	pos = Get_Hash_Key(id);

	for (;;)
	{
		if (Hash_table[pos].id == id) return &Hash_table[pos];
		if (Hash_table[pos].id == -1) return (SCORE*)0;
		pos += STEP;
		cnt++;
		search_cnt += cnt + 1;
		printf("cnt = %d, total search count = %d\n", cnt + 1, search_cnt);
		if (cnt >= MAX_ST) return (SCORE*)0;
		if (pos >= MAX_ST) pos %= MAX_ST;
	}
}

#endif

/***********************************************************/
// [2-2.6] Insert 효율
/***********************************************************/

#if 0

void main(void)
{
	int i;
	int r;

	Init_Hash_Table();

	for (i = 0; i < MAX_ST; i++)
	{
		printf("[Loop: %d] Inserted Position=%d, ID=%d\n", i, r = Insert_Data(&test[i]), test[i].id);
		Print_All_Data();
	}
}

#endif

/***********************************************************/
// [2-2.7] Search 효율
/***********************************************************/

#if 0

void main(void)
{
	int i;
	int r;
	SCORE* p;

	Init_Hash_Table();

	for (i = 0; i < 15; i++)
	{
		printf("[Loop: %d] Inserted Position=%d, ID=%d\n", i, r = Insert_Data(&test[i]), test[i].id);
	}

	Print_All_Data();
	printf("Serch Result=0x%.8X\n", p = Search_Data(3));
	if (p) printf("ID=%d, NAME=%s\n", p->id, p->name);
	printf("Serch Result=0x%.8X\n", p = Search_Data(12));
	if (p) printf("ID=%d, NAME=%s\n", p->id, p->name);
	printf("Serch Result=0x%.8X\n", p = Search_Data(25));
	if (p) printf("ID=%d, NAME=%s\n", p->id, p->name);
}

#endif

/***********************************************************/
// [2-2.8] Insert, Search, Delete
/***********************************************************/

#if 0

void main(void)
{
	int i;
	int r;

	Init_Hash_Table();

	for (i = 0; i < 15; i++)
	{
		printf("[Loop: %d] Inserted Position=%d, ID=%d\n", i, r = Insert_Data(&test[i]), test[i].id);
	}

	Print_All_Data();
	printf("[3] Delete Result=%d\n", r = Delete_Data(3));
	printf("[12] Delete Result=%d\n", r = Delete_Data(12));
	printf("[25] Delete Result=%d\n", r = Delete_Data(25));
	printf("[3] Delete Result=%d\n", r = Delete_Data(3));
	printf("[12] Delete Result=%d\n", r = Delete_Data(12));
	Print_All_Data();

	printf("Inserted Position=%d, ID=%d\n", r = Insert_Data(&test[13]), test[13].id);
	printf("Inserted Position=%d, ID=%d\n", r = Insert_Data(&test[5]), test[5].id);
	Print_All_Data();
}

#endif

#endif

/***********************************************************/
// [2-2.9] Hash Table => Chainning 방법의 구현
/***********************************************************/

#if 0

/***********************************************************/
// [2-2.9] Hash Table을 위한 기본 함수들
/***********************************************************/

#if 0

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <malloc.h>

typedef struct _score
{
	int id;
	int jumsu;
	char name[10];
	struct _score* next;
}SCORE;

#define MAX_ST		20
#define HASH_KEY	5

SCORE Hash_table[HASH_KEY]; // Linked List의 Head 배열



int Create_Data(SCORE* p);
int Get_Hash_Key(int id);
void Init_Hash_Table(void);
void Print_All_Data(void);
int Insert_Data(SCORE* d);
SCORE* Search_Data(int id);
int Delete_Data(int id);

SCORE test[MAX_ST + 2] = { {10, 50, "kim"}, {2, 80, "lew"}, {8, 50, "lew"}, {4, 45, "lee"}, {1, 90, "song"},\
							   {3, 45, "kim"}, {5, 50, "song"}, {9, 100, "lee"}, {7, 75, "moon"}, {6, 90, "park"}, \
							   {15, 90, "ki"}, {11, 20, "kong"}, {14, 40, "shin"}, {12, 50, "son"}, {17, 48, "lee"}, \
							   {20, 100, "min"}, {19, 80, "you"}, {13, 45, "song"}, {16, 54, "no"}, {18, 100, "yang"}, \
							   {21, 58, "seo"}, {23, 88, "oh"} };

int Create_Data(SCORE* p)
{
	printf("\n사번을 입력하세요 => ");
	scanf("%d", &p->id);
	fflush(stdin);
	printf("이름을 입력하세요 => ");
	scanf("%s", p->name);
	fflush(stdin);
	printf("점수를 입력하세요 => ");
	scanf("%d", &p->jumsu);
	fflush(stdin);

	return 1;
}

int Get_Hash_Key(int id)
{
	return id % HASH_KEY;
}

void Init_Hash_Table(void)
{
	int i;

	for (i = 0; i < HASH_KEY; i++)
	{
		Hash_table[i].next = (SCORE*)0;
	}
}

void Print_All_Data(void)
{
	int i;
	SCORE* p;

	for (i = 0; i < HASH_KEY; i++)
	{
		p = Hash_table[i].next;

		for (;;)
		{
			if (p == (SCORE*)0) break;
			printf("[%d] address:0x%.8X, ID: %d, NAME: %s, next: 0x%.8X\n", i, p, p->id, p->name, p->next);
			p = p->next;
		}
	}
}

#endif

/***********************************************************/
// [2-2.10] Insert
/***********************************************************/

#if 0

int Insert_Data(SCORE* d)
{
	SCORE* newnode;
	if (Search_Data(d->id) != (SCORE*)0) return -2;
	
	newnode = (SCORE*)calloc(1, sizeof(SCORE));
	if (newnode == (SCORE*)0) return -1;

	*newnode = *d;

	int hash = Get_Hash_Key(newnode->id);

	newnode->next = Hash_table[hash].next;
	Hash_table[hash].next = newnode;
	
	return 1;
}

// 정렬로 효율 높이기
/*
int Insert_Data(SCORE* d)
{
	SCORE* newnode;
	SCORE* prev;

	int hash = Get_Hash_Key(d->id);
	prev = &Hash_table[hash];

	while (prev->next) {
		if (prev->next->id > d->id) break;
		if (prev->next->id == d->id) return -2;
		prev = prev->next;
	}
	newnode = (SCORE*)calloc(1, sizeof(SCORE));
	if (newnode == (SCORE*)0) return -1;

	*newnode = *d;
	newnode->next = prev.next;
	prev.next = newnode;
	return 1;
}
*/

#endif

#if 0

void main(void)
{
	int i;
	int r;

	Init_Hash_Table();

	for (i = 0; i < MAX_ST; i++)
	{
		printf("[Loop: %d] Insert Result=%d, ID=%d\n", i, r = Insert_Data(&test[i]), test[i].id);
		Print_All_Data();
	}
}

#endif

/***********************************************************/
// [2-2.11] Delete
/***********************************************************/

#if 0

int Delete_Data(int id)
{
	int hash = Get_Hash_Key(id);
	SCORE* prev = &Hash_table[hash];
	SCORE* delnode;

	while (prev->next) {
		if (prev->next->id == id) {
			delnode = prev->next;
			prev->next = prev->next->next;
			free(delnode);
			return 1;
		}
		// if (prev->next->id > id) break; 정렬로 삭제 효율 높이기
	}
	return -1;
}

#endif

#if 0

void main(void)
{
	int i;
	int r;

	Init_Hash_Table();

	for (i = 0; i < MAX_ST; i++) printf("[Loop: %d] Insert Result=%d, ID=%d\n", i, r = Insert_Data(&test[i]), test[i].id);
	Print_All_Data();

	printf("[1] Delete Result=%d\n", r = Delete_Data(1));
	printf("[11] Delete Result=%d\n", r = Delete_Data(11));
	printf("[16] Delete Result=%d\n", r = Delete_Data(16));
	printf("[9] Delete Result=%d\n", r = Delete_Data(9));
	printf("[10] Delete Result=%d\n", r = Delete_Data(10));
	Print_All_Data();

	printf("Inserted Position=%d, ID=%d\n", r = Insert_Data(&test[1]), test[1].id);
	printf("Inserted Position=%d, ID=%d\n", r = Insert_Data(&test[11]), test[11].id);
	Print_All_Data();
}

#endif

/***********************************************************/
// [2-2.12] Search
/***********************************************************/

#if 0

SCORE* Search_Data(int id)
{
	int hash = Get_Hash_Key(id);
	SCORE* node = Hash_table[hash].next;

	while (node) {
		if (node->id == id) return node;
		// if (node->id > id) break; 정렬로 탐색 효율 높이기
		node = node->next;
	}
	return (SCORE*)0;
}

#endif

#if 0

void main(void)
{
	int i;
	int r;
	SCORE* p;

	Init_Hash_Table();

	for (i = 0; i < MAX_ST; i++) printf("[Loop: %d] Insert Result=%d, ID=%d\n", i, r = Insert_Data(&test[i]), test[i].id);
	Print_All_Data();

	printf("Serch Result=0x%.8X\n", p = Search_Data(3));
	if (p) printf("[%d] address:0x%.8X, ID: %d, NAME: %s, next: 0x%.8X\n", i, p, p->id, p->name, p->next);
	printf("Serch Result=0x%.8X\n", p = Search_Data(12));
	if (p) printf("[%d] address:0x%.8X, ID: %d, NAME: %s, next: 0x%.8X\n", i, p, p->id, p->name, p->next);
	printf("Serch Result=0x%.8X\n", p = Search_Data(25));
	if (p) printf("[%d] address:0x%.8X, ID: %d, NAME: %s, next: 0x%.8X\n", i, p, p->id, p->name, p->next);
}

#endif

#endif

/***********************************************************/
// [2-3] Tree
/***********************************************************/

/***********************************************************/
// [2-3-1] Heap
/***********************************************************/
#if 0

/***********************************************************/
// [2-3-1.1] Heap 자료
/***********************************************************/
#if 0
#include <stdio.h>

#define NUM_DATA	(8)
#define MAX_DATA	(NUM_DATA)
#define MAX_HEAP	(MAX_DATA+1)
#define LAST_NODE	(MAX_DATA)

int heap[MAX_HEAP];
int lastnode = 0;

int exam[NUM_DATA + 1] = { 0,4,8,2,7,1,3,6,5 }; // 0번 index 공간 무시

#define PRINT_TREE {int j;printf("( ");	for(j=1;j<=LAST_NODE;j++){printf("%3d ",heap[j]);}printf(")\n");}

int Heap_Push_Minheap(int* heap, int size, int* lastnode, int d);
int Heap_Pop_Minheap(int* heap, int* lastnode, int* d);
int Heap_Push_Maxheap(int* heap, int size, int* lastnode, int d);
int Heap_Pop_Maxheap(int* heap, int* lastnode, int* d);
void Heap_Sort(int* data, int cnt, int order);

#endif

/***********************************************************/
// [2-3-1.2] Heap Push (Min Heap)
/***********************************************************/
#if 0
int Heap_Push_Minheap(int* heap, int size, int* lastnode, int d)
// heap : control할 heap 배열의 시작 주소, lastnode의 값은 변경되기 때문에 주솟값을 받는다.
{
	if (size == *lastnode) return -1; // 가득 찼다.

	heap[++*lastnode] = d; // lastnode를 변경해야하므로 latnode + 1 대신 ++lastnode

	int child = *lastnode;
	int parent = child / 2;
	while (parent) {
		if (heap[child] < heap[parent]) {
			int tmp = heap[child];
			heap[child] = heap[parent];
			heap[parent] = tmp;

			child = parent; parent = child / 2;
		}
		else break;
	}
	return 1;
}
#endif

#if 0
int main(void)
{
	int i;
	printf("Heap Push Test (Minheap)\n");

	for (i = 1; i <= NUM_DATA; i++)
	{
		printf("[%d] Heap_Push_Minheap(%d) => %d", i, exam[i], Heap_Push_Minheap(heap, MAX_DATA, &lastnode, exam[i]));
		PRINT_TREE;
	}
	printf("[9] Heap_Push_Minheap(9) => %d\n", Heap_Push_Minheap(heap, MAX_DATA, &lastnode, 9));

	return 0;
}
#endif

/***********************************************************/
// [2-3-1.3] Heap Pop (Min Heap)
/***********************************************************/
#if 0
int Heap_Pop_Minheap(int* heap, int* lastnode, int* d)
{
	int node, Lchild, Rchild, child;
	if (*lastnode == 0) return -1;

	*d = heap[1];
	heap[1] = heap[(*lastnode)--]; // *lastnode--는 연산자 우선순위에 의해 *(lastnode--)가 된다.

	node = 1, Lchild = 2, Rchild = 3;
	while (Lchild <= *lastnode) { // node가 아니라 Lchild로 비교해야함 -> 자식이 있어야하므로
		if (Lchild == *lastnode) child = Lchild;
		else child = (heap[Lchild] < heap[Rchild]) ? Lchild : Rchild;

		if (heap[child] < heap[node]) {
			int tmp = heap[child];
			heap[child] = heap[node];
			heap[node] = tmp;

			node = child; Lchild = child * 2; Rchild = child * 2 + 1; // or Rchild = Lchild + 1;
		}
		else break;
	}
	return 1;
}
#endif

#if 0
int main(void)
{
	int i, ret;
	printf("Heap Pop Test (Minheap)\n");

	for (i = 1; i <= NUM_DATA; i++)
	{
		printf("[%d] Heap_Push_Minheap(%d) => %d", i, exam[i], Heap_Push_Minheap(heap, MAX_DATA, &lastnode, exam[i]));
		PRINT_TREE;
	}

	for (i = 1; i <= NUM_DATA; i++)
	{
		printf("[%d] Heap_Pop_Minheap() => %d - ", i, Heap_Pop_Minheap(heap, &lastnode, &ret));
		printf("%d\n", ret);
	}
	printf("[9] Heap_Pop_Minheap() => %d\n", Heap_Pop_Minheap(heap, &lastnode, &ret));

	return 0;
}

#endif


/***********************************************************/
// [2-3-1.4] Heap Push (Max Heap)
/***********************************************************/
#if 0
int Heap_Push_Maxheap(int* heap, int size, int* lastnode, int d)
{
	if (*lastnode == size) return -1;

	heap[++(*lastnode)] = d;
	int node = *lastnode;
	int parent = node / 2;
	while (parent) {
		if (heap[node] > heap[parent]) {
			int tmp = heap[node];
			heap[node] = heap[parent];
			heap[parent] = tmp;

			node = parent;
			parent = node / 2;
		}
		else break;
	}
	return 1;
}

#endif

#if 0
int main(void)
{
	int i;
	printf("Heap Push Test (Maxheap)\n");

	for (i = 1; i <= NUM_DATA; i++)
	{
		printf("[%d] Heap_Push_Maxheap(%d) => %d", i, exam[i], Heap_Push_Maxheap(heap, MAX_DATA, &lastnode, exam[i]));
		PRINT_TREE;
	}
	printf("[9] Heap_Push_Maxheap(9) => %d\n", Heap_Push_Maxheap(heap, MAX_DATA, &lastnode, 9));

	return 0;
}
#endif

/***********************************************************/
// [2-3-1.5] Heap Pop (Max Heap)
/***********************************************************/
#if 0
int Heap_Pop_Maxheap(int* heap, int* lastnode, int* d)
{
	int node, Lchild, Rchild, child;

	if (*lastnode == 0) return -1;

	*d = heap[1];
	heap[1] = heap[(*lastnode)--];

	node = 1, Lchild = 2, Rchild = 3;
	while (Lchild <= *lastnode) {
		if (Lchild == *lastnode) child = Lchild;
		else child = (heap[Lchild] > heap[Rchild]) ? Lchild : Rchild;

		if (heap[node] < heap[child]) {
			int tmp = heap[node];
			heap[node] = heap[child];
			heap[child] = tmp;

			node = child; Lchild = node * 2; Rchild = node * 2 + 1;
		}
		else break;
	}
	return 1;
}

#endif

#if 0
int main(void)
{
	int i, ret;
	printf("Heap Pop Test (Maxheap)\n");

	for (i = 1; i <= NUM_DATA; i++)
	{
		printf("[%d] Heap_Push_Maxheap(%d) => %d", i, exam[i], Heap_Push_Maxheap(heap, MAX_DATA, &lastnode, exam[i]));
		PRINT_TREE;
	}

	for (i = 1; i <= NUM_DATA; i++)
	{
		printf("[%d] Heap_Pop_Maxheap() => %d - ", i, Heap_Pop_Maxheap(heap, &lastnode, &ret));
		printf("%d\n", ret);
	}
	printf("[9] Heap_Pop_Maxheap() => %d\n", Heap_Pop_Maxheap(heap, &lastnode, &ret));

	return 0;
}

#endif

/***********************************************************/
// [2-3-1.6] Heap Sort
/***********************************************************/
#if 0
typedef int (*HEAP_PUSH)(int*, int, int*, int);
typedef int (*HEAP_POP)(int*, int*, int*);

void Heap_Sort(int* data, int cnt, int order)
{
	if (order) {
		for (int i = 0; i < cnt; i++) {
			Heap_Push_Minheap(data - 1, cnt, &lastnode, data[i]); // data - 1 : data의 인덱스 하나 앞을 주어야 0번 인덱스가 heap의 1번 인덱스로 들어간다.
		}
		for (int i = cnt - 1; i >= 0; i--) {
			int ret;
			Heap_Pop_Minheap(data - 1, &lastnode, &ret);
			data[i] = ret;
		}
	}
	else {
		for (int i = 0; i < cnt; i++) {
			Heap_Push_Maxheap(data - 1, cnt, &lastnode, data[i]); // data - 1 : data의 인덱스 하나 앞을 주어야 0번 인덱스가 heap의 1번 인덱스로 들어간다.
		}
		for (int i = cnt - 1; i >= 0; i--) {
			int ret;
			Heap_Pop_Maxheap(data - 1, &lastnode, &ret);
			data[i] = ret;
		}
	}
	/*
	[일반화 - 함수의 포인터]
	
	HEAP_PUSH arr_push[] = { Heap_Push_Maxheap, Heap_Push_Minheap };
	HEAP_POP arr_pop[] = { Heap_Pop_Maxheap, Heap_Pop_Minheap };

	HEAP_PUSH push = arr_push[order];
	HEAP_POP pop = arr_pop[order];

	for (int i = 0; i < cnt; i++) {
		push(data - 1, cnt, &lastnode, data[i]); // data - 1 : data의 인덱스 하나 앞을 주어야 0번 인덱스가 heap의 1번 인덱스로 들어간다.
	}
	for (int i = cnt - 1; i >= 0; i--) {
		int ret;
		pop(data - 1, &lastnode, &ret);
		data[i] = ret;
	}
	*/
}

#endif

#if 0
int main(void)
{
	int i, data[NUM_DATA + 1];
	printf("Heap Sort Test\n\n");

	printf("Original data : ");
	for (i = 0; i < NUM_DATA; i++)
	{
		data[i] = exam[i + 1];
		printf("%d ", data[i]);
	}
	printf("\n");

	Heap_Sort(data, NUM_DATA, 0); // 0은 오름차순, 1은 내림차순
	printf("Sorted data : ");
	for (i = 0; i < NUM_DATA; i++)
	{
		printf("%d ", data[i]);
	}
	printf("\n");

	return 0;
}

#endif


#endif


/***********************************************************/
// [2-3-2.1~4] Segment Tree
/***********************************************************/

#if 1

/***********************************************************/
// [2-3-2.1] Segment Tree 자료 확인
/***********************************************************/
#if 1
#include <stdio.h>

#define NUM_DATA	(5)
#define MAX_DATA	(NUM_DATA)
#define MAX_TREE	(8*2) // 8 = 5보다 큰 2의 제곱수 중 최솟값
#define LAST_NODE	(MAX_DATA*2-1)

int tree[MAX_TREE];

int exam[NUM_DATA + 1] = { 0,1,2,3,4,5 }; // 0번 index 공간 무시

#define PRINT_TREE {int j;printf("( ");	for(j=1;j<=LAST_NODE;j++){printf("%3d ",tree[j]);}printf(")\n");}

void Update_New_Data(int node, int s, int e, int idx, int data);
void Update_Add(int node, int s, int e, int us, int ue, int add);
int Query(int node, int s, int e, int qs, int qe);
#endif
/***********************************************************/
// [2-3-2.2] 새로운 데이터의 추가 및 데이터 업데이트 함수
/***********************************************************/
#if 1
void Update_New_Data(int node, int s, int e, int idx, int data) // node : node 번호, s ~ e : 구간, idx : 해당 노드에 들어갈 데이터의 인덱스 = leaf 노드만 봤을 때 인덱스
{
	int mid;
	if (s == e) { // 데이터 한개짜리 leaf node
		tree[node] = data;
		return;
	}
	// 왼쪽으로 내려갈까 오른쪽으로 내려갈까?
	mid = (s + e) / 2;
	if (idx <= mid) Update_New_Data(node * 2, s, mid, idx, data);
	else Update_New_Data(node * 2 + 1, mid + 1, e, idx, data);

	tree[node] = tree[node * 2] + tree[node * 2 + 1];
}
#endif

#if 1
void main(void)
{
	int i;

	printf("Update_New_Data() Test\n");

	for (i = 1; i <= NUM_DATA; i++)
	{
		Update_New_Data(1, 1, NUM_DATA, i, exam[i]);
		printf("[%d] data : %d ", i, exam[i]);
		PRINT_TREE;
	}
}
#endif


/***********************************************************/
// [2-3-2.3] 구간 정보 요청
/***********************************************************/
#if 0
int Query(int node, int s, int e, int qs, int qe) // 앞에 3개는 노드 정보, 뒤에 2개는 쿼리 정보
{
	int Lresult, Rresult;
	if (qs <= s && e <= qe) { // 노드 구간이 질문 구간의 내부 구간인가?     qs <-----> qe
		return tree[node]; // 해당 노드의 값 return								s <--> e
	}
	else if (e < qs || qe < s) { // 노드 구간과 질문 구간이 전혀 관계가 없다면?       qs <-----> qe
		return 0;	// 연산에 영향을 주지 않을만한 값 return				s <--> e		or		s <--> e
	}
	// 일부만 겹침										qs <-----> qe
	int mid = (s + e) / 2;						//	   s <--> e
	Lresult = Query(node * 2, s, mid, qs, qe); // s ~ mid와 쿼리 구간을 다시 비교
	Rresult = Query(node * 2 + 1, mid + 1, e, qs, qe); // mid + 1 ~ e와 쿼리 구간을 다시 비교
	return Lresult + Rresult;
}
#endif

#if 0
void main(void)
{
	int i;

	printf("Query() Test\n");

	for (i = 1; i <= NUM_DATA; i++)
	{
		Update_New_Data(1, 1, NUM_DATA, i, exam[i]);
	}

	printf("Query[1~5] : result = %d\n", Query(1, 1, NUM_DATA, 1, 5));
	printf("Query[1~3] : result = %d\n", Query(1, 1, NUM_DATA, 1, 3));
	printf("Query[4~5] : result = %d\n", Query(1, 1, NUM_DATA, 4, 5));
	printf("Query[2~4] : result = %d\n", Query(1, 1, NUM_DATA, 2, 4));
	printf("Query[3~5] : result = %d\n", Query(1, 1, NUM_DATA, 3, 5));
}
#endif


/*************************************************************/
// [2-3-2.4] 특정 구간 데이터 변경 함수 - 데이터 증가/감소
/*************************************************************/
#if 0
void Update_Add(int node, int s, int e, int us, int ue, int add)
{
	if (e < us || ue < s) { // 노드 구간과 질문 구간이 전혀 관계가 없다면?       us <-----> ue
		return;													  //   s <--> e		or		s <--> e
	}
	if (s == e) { // 데이터 한개짜리 leaf node
		tree[node] += add;
		return;
	}
	// 위의 두개의 if문 순서를 바꾸면 s = 1, e = 1이 들어왔을 때 범위에 맞지 않는데도 +add가 된다.

	int mid = (s + e) / 2;
	Update_Add(node * 2, s, mid, us, ue, add);
	Update_Add(node * 2 + 1, mid + 1, e, us, ue, add);

	tree[node] = tree[node * 2] + tree[node * 2 + 1];
}
#endif

#if 0
void main(void)
{
	int i;

	printf("Update_Add() Test\n");

	for (i = 1; i <= NUM_DATA; i++)
	{
		Update_New_Data(1, 1, NUM_DATA, i, exam[i]);
	}

	printf("[Before Range Update] ");
	PRINT_TREE;
	printf("Query[1~5] : result = %d\n", Query(1, 1, NUM_DATA, 1, 5));
	printf("Query[1~3] : result = %d\n", Query(1, 1, NUM_DATA, 1, 3));
	printf("Query[4~5] : result = %d\n", Query(1, 1, NUM_DATA, 4, 5));
	printf("Query[2~4] : result = %d\n", Query(1, 1, NUM_DATA, 2, 4));
	printf("Query[3~5] : result = %d\n", Query(1, 1, NUM_DATA, 3, 5));

	Update_Add(1, 1, NUM_DATA, 2, 4, 2);

	printf("\n[After Range Update] ");
	PRINT_TREE;
	printf("Query[1~5] : result = %d\n", Query(1, 1, NUM_DATA, 1, 5));
	printf("Query[1~3] : result = %d\n", Query(1, 1, NUM_DATA, 1, 3));
	printf("Query[4~5] : result = %d\n", Query(1, 1, NUM_DATA, 4, 5));
	printf("Query[2~4] : result = %d\n", Query(1, 1, NUM_DATA, 2, 4));
	printf("Query[3~5] : result = %d\n", Query(1, 1, NUM_DATA, 3, 5));
}
#endif
#endif


/***********************************************************/
// [2-3-2.5~9] Segment Tree with Lazy Propagation
/***********************************************************/

#if 0

/***********************************************************/
// [2-3-2.5] Segment Tree with Lazy Propagation 자료 확인
/***********************************************************/
#if 0
#include <stdio.h>

#define NUM_DATA	(5)
#define MAX_DATA	(NUM_DATA)
#define MAX_TREE	(8*2)
#define LAST_NODE	(MAX_DATA*2-1)

int tree[MAX_TREE];
int lazy[MAX_TREE];

int exam[NUM_DATA + 1] = { 0,1,2,3,4,5 }; // 0번 index 공간 무시

#define PRINT_TREE {int j;printf("( ");	for(j=1;j<=LAST_NODE;j++){printf("%3d ",tree[j]);}printf(")\n");}

void Propagate(int n, int s, int e);
void Update_New_Data_Lazy(int node, int s, int e, int idx, int data);
void Update_Add_Lazy(int node, int s, int e, int us, int ue, int add);
int Query_Lazy(int node, int s, int e, int qs, int qe);
#endif


/***********************************************************/
// [2-3-2.6] Propagate 함수
/***********************************************************/
#if 0

void Propagate(int node, int s, int e)
{
	if (lazy[node]) {
		if (s != e) { // 자식이 하나일 수는 없다! = 둘이거나 없거나
			lazy[node * 2] += lazy[node];
			lazy[node * 2 + 1] += lazy[node];
		}
		tree[node] += (e - s + 1) * lazy[node];
		lazy[node] = 0;
	}
}
#endif

/***********************************************************/
// [2-3-2.7] 새로운 data 추가/Update
/***********************************************************/

#if 0
void Update_New_Data_Lazy(int node, int s, int e, int idx, int data)
{
	Propagate(node, s, e);

	if (idx < s || e < idx) return;
	if (s == e) {
		tree[node] = data;
		return;
	}
	int mid = (s + e) / 2;

	Update_New_Data_Lazy(node * 2, s, mid, idx, data);
	Update_New_Data_Lazy(node * 2 + 1, mid + 1, e, idx, data);

	tree[node] = tree[node * 2] + tree[node * 2 + 1];
}
#endif

#if 0
void main(void)
{
	int i;

	printf("Update_New_Data() Test\n");

	for (i = 1; i <= NUM_DATA; i++)
	{
		Update_New_Data_Lazy(1, 1, NUM_DATA, i, exam[i]);
		printf("[%d] data : %d ", i, exam[i]);
		PRINT_TREE;
	}
}
#endif


/***********************************************************/
// [2-3-2.8] 구간 정보 요청
/***********************************************************/
#if 0
int Query_Lazy(int node, int s, int e, int qs, int qe)
{
	int mid, Lresult, Rresult;
	Propagate(node, s, e);

	if (qs <= s && e <= qe) return tree[node];
	else if (qe < s || e < qs) return 0;

	mid = (s + e) / 2;
	Lresult = Query_Lazy(node * 2, s, mid, qs, qe);
	Rresult = Query_Lazy(node * 2 + 1, mid + 1, e, qs, qe);

	return Lresult + Rresult;
}
#endif

#if 0
void main(void)
{
	int i;

	printf("Query() Test\n");

	for (i = 1; i <= NUM_DATA; i++)
	{
		Update_New_Data_Lazy(1, 1, NUM_DATA, i, exam[i]);
	}

	printf("Query[1~5] : result = %d\n", Query_Lazy(1, 1, NUM_DATA, 1, 5));
	printf("Query[1~3] : result = %d\n", Query_Lazy(1, 1, NUM_DATA, 1, 3));
	printf("Query[4~5] : result = %d\n", Query_Lazy(1, 1, NUM_DATA, 4, 5));
	printf("Query[2~4] : result = %d\n", Query_Lazy(1, 1, NUM_DATA, 2, 4));
	printf("Query[3~5] : result = %d\n", Query_Lazy(1, 1, NUM_DATA, 3, 5));
}
#endif


/*************************************************************/
// [2-3-2.9] 특정 구간 데이터 변경 함수 - 데이터 증가/감소
/*************************************************************/
#if 0
void Update_Add_Lazy(int node, int s, int e, int us, int ue, int add)
{
	Propagate(node, s, e);

	if (e < us || ue < s) return;
	if (us <= s && e <= ue) {
		lazy[node] = add; // Propagte을 했기 때문에 lazy[node]는 0일 것임 +=add로 안 해도 OK
		Propagate(node, s, e);
		return;
	}

	int mid = (s + e) / 2;
	Update_Add_Lazy(node * 2, s, mid, us, ue, add);
	Update_Add_Lazy(node * 2 + 1, mid + 1, e, us, ue, add);

	tree[node] = tree[node * 2] + tree[node * 2 + 1];
}
#endif

#if 0
void main(void)
{
	int i;

	printf("Update_Add() Test\n");

	for (i = 1; i <= NUM_DATA; i++)
	{
		Update_New_Data_Lazy(1, 1, NUM_DATA, i, exam[i]);
	}

	printf("[Before Range Update] ");
	PRINT_TREE;
	printf("Query[1~5] : result = %d\n", Query_Lazy(1, 1, NUM_DATA, 1, 5));
	printf("Query[1~3] : result = %d\n", Query_Lazy(1, 1, NUM_DATA, 1, 3));
	printf("Query[4~5] : result = %d\n", Query_Lazy(1, 1, NUM_DATA, 4, 5));
	printf("Query[2~4] : result = %d\n", Query_Lazy(1, 1, NUM_DATA, 2, 4));
	printf("Query[3~5] : result = %d\n", Query_Lazy(1, 1, NUM_DATA, 3, 5));

	Update_Add_Lazy(1, 1, NUM_DATA, 2, 4, 2);

	printf("\n[After Range Update] ");
	PRINT_TREE;
	printf("Query[1~5] : result = %d\n", Query_Lazy(1, 1, NUM_DATA, 1, 5));
	printf("Query[1~3] : result = %d\n", Query_Lazy(1, 1, NUM_DATA, 1, 3));
	printf("Query[4~5] : result = %d\n", Query_Lazy(1, 1, NUM_DATA, 4, 5));
	printf("Query[2~4] : result = %d\n", Query_Lazy(1, 1, NUM_DATA, 2, 4));
	printf("Query[3~5] : result = %d\n", Query_Lazy(1, 1, NUM_DATA, 3, 5));
}
#endif
#endif


/***********************************************************/
// [2-3-3] Fenwick Tree
/***********************************************************/

#if 0

/***********************************************************/
// [2-3-3.1] Fenwick Tree �ڷ� Ȯ��
/***********************************************************/
#if 0
#include <stdio.h>

#define NUM_DATA	(16)
#define MAX_DATA	(NUM_DATA)
#define MAX_TREE	(MAX_DATA+1)
#define LAST_NODE	(MAX_DATA)

#define LSB(X) ((X)&(-(X)))

int fenwick_tree[MAX_TREE];
int exam[NUM_DATA + 1] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 }; // 0�� index ���� ����

#define PRINT_TREE {int j;printf("( ");	for(j=1;j<=LAST_NODE;j++){printf("%3d ",fenwick_tree[j]);}printf(")\n");}


// �������� ����Ǵ� ��� �Լ��� �� �κп� ������ �߰��Ѵ�
void Init_Fenwick_Tree(void);
int Get_Psum(int idx);
void Update_Add(int idx, int val);
#endif

/***********************************************************/
// [2-3-3.2] Fenwick Tree �ʱ�ȭ
/***********************************************************/
#if 0
void Init_Fenwick_Tree(void)
{






}
#endif

#if 0
int main(void)
{
	int i;
	for (i = 1; i <= MAX_DATA; i++)
	{
		fenwick_tree[i] = exam[i];
	}

	printf("Fenwick Tree Initialization Test\n\n");

	Init_Fenwick_Tree();

	PRINT_TREE;

	return 0;
}
#endif

/***********************************************************/
// [2-3-3.3] Fenwick Tree Prefix Sum ���
/***********************************************************/
#if 0
int Get_Psum(int idx)
{






}
#endif

#if 0
int main(void)
{
	int i;
	for (i = 1; i <= MAX_DATA; i++)
	{
		fenwick_tree[i] = exam[i];
	}

	printf("Fenwick Tree prefix sum Test\n");
	Init_Fenwick_Tree();

	PRINT_TREE;

	printf("\n[Prefix Sum]\n");
	printf("Prefix sum[3] = %d\n", Get_Psum(3));
	printf("Prefix sum[5] = %d\n", Get_Psum(5));
	printf("Prefix sum[8] = %d\n", Get_Psum(8));
	printf("Prefix sum[10] = %d\n", Get_Psum(10));
	printf("Prefix sum[13] = %d\n", Get_Psum(13));

	printf("\n[Interval Sum]\n");
	printf("Sum [3~5] = %d\n", Get_Psum(5) - Get_Psum(3 - 1));
	printf("Sum [2~7] = %d\n", Get_Psum(7) - Get_Psum(2 - 1));
	printf("Sum [6~13] = %d\n", Get_Psum(13) - Get_Psum(6 - 1));

	return 0;
}
#endif

/***********************************************************/
// [2-3-3.4] ���� �� ����
/***********************************************************/
#if 0
void Update_Add(int idx, int val)
{





}
#endif

#if 0
int main(void)
{
	int i;
	for (i = 1; i <= MAX_DATA; i++)
	{
		fenwick_tree[i] = exam[i];
	}

	printf("Fenwick Tree Uadate Test\n");
	Init_Fenwick_Tree();

	PRINT_TREE;

	printf("[Prefix Sum]\n");
	printf("Prefix sum[3] = %d\n", Get_Psum(3));
	printf("Prefix sum[5] = %d\n", Get_Psum(5));
	printf("Prefix sum[8] = %d\n", Get_Psum(8));

	Update_Add(4, 2);

	printf("\n[Prefix Sum after Update]\n");
	printf("Prefix sum[3] = %d\n", Get_Psum(3));
	printf("Prefix sum[5] = %d\n", Get_Psum(5));
	printf("Prefix sum[8] = %d\n", Get_Psum(8));

	return 0;
}
#endif
#endif

/***********************************************************/
// [2-3-4] Binary Search Tree
/***********************************************************/

#if 0

/***********************************************************/
// [2-3-4.1] ���� Tree�� �μ�
/***********************************************************/

#if 0

#include <stdio.h>

struct node
{
	const char* name; // cpp에서는 const를 붙여주어야함
	struct node* left;
	struct node* right;
};

void Print_All_Node1(struct node* p);
void Print_All_Node2(struct node* p);
void Print_All_Node3(struct node* p);

void main(void)
{
	struct node root, node1, node2, node3, node4;

	root.left = &node1;
	root.right = &node2;
	root.name = "root";
	node1.left = &node3;
	node1.right = &node4;
	node1.name = "node1";
	node2.left = NULL;
	node2.right = NULL;
	node2.name = "node2";
	node3.left = NULL;
	node3.right = NULL;
	node3.name = "node3";
	node4.left = NULL;
	node4.right = NULL;
	node4.name = "node4";

	printf("In-order Traverse===============\n");
	Print_All_Node1(&root);
	printf("Pre-order Traverse===============\n");
	Print_All_Node2(&root);
	printf("Post-order Traverse===============\n");
	Print_All_Node3(&root);
}

void Print_All_Node1(struct node* p)
{
	if (p->left) Print_All_Node1(p->left);
	printf("Name = %s\n", p->name);
	if (p->right) Print_All_Node1(p->right);
}

void Print_All_Node2(struct node* p)
{
	printf("Name = %s\n", p->name);
	if (p->left) Print_All_Node2(p->left);
	if (p->right) Print_All_Node2(p->right);
}

void Print_All_Node3(struct node* p)
{
	if (p->left) Print_All_Node3(p->left);
	if (p->right) Print_All_Node3(p->right);
	printf("Name = %s\n", p->name);
}

#endif

/***********************************************************/
// [2-3-4.2] 이진 트리를 위한 기본 함수들
/***********************************************************/

#if 0

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <malloc.h>

typedef struct _score
{
	int id;
	int jumsu;
	char name[10];
	struct _score* left;
	struct _score* right;
	struct _score* parent;
}SCORE;

SCORE* Root;

#define MAX_ST		20

void Print_All_Node(SCORE* p);
void Delete_All_Node(SCORE* p);
int Insert_Node(SCORE* head, SCORE* d);
SCORE* Search_Node(SCORE* head, int id);
int Delete_Node(SCORE* head, int id);
SCORE* Creat_Node(SCORE* d);
int Create_Data(SCORE* p);

SCORE test[MAX_ST] = { { 10, 50, "kim" }, { 2, 80, "lew" }, { 8, 50, "lew" }, { 4, 45, "lee" }, { 1, 90, "song" }, \
{3, 45, "kim"}, { 5, 50, "song" }, { 9, 100, "lee" }, { 7, 75, "moon" }, { 6, 90, "park" }, \
{15, 90, "ki"}, { 11, 20, "kong" }, { 14, 40, "shin" }, { 12, 50, "son" }, { 17, 48, "lee" }, \
{20, 100, "min"}, { 19, 80, "you" }, { 13, 45, "song" }, { 16, 54, "no" }, { 18, 100, "yang" } };

int Create_Data(SCORE* p)
{
	printf("\n사번을 입력하세요 => ");
	scanf("%d", &p->id);
	fflush(stdin);
	printf("이름을 입력하세요 => ");
	scanf("%s", p->name);
	fflush(stdin);
	printf("점수를 입력하세요 => ");
	scanf("%d", &p->jumsu);
	fflush(stdin);
	p->left = (SCORE*)0x0;
	p->right = (SCORE*)0x0;

	return 1;
}

void Print_All_Node(SCORE* p)
{

	if (p == (SCORE*)0)
	{
		printf("No Data\n");
		return;
	}

	if (p->left) Print_All_Node(p->left);
	printf("addr=0x%.8X, ID=%d, left=0x%.8X, right=0x%.8X, parent=0x%.8X\n", p, p->id, p->left, p->right, p->parent);
	if (p->right) Print_All_Node(p->right);
}

#endif

/***********************************************************/
// [2-3-4.3] 데이터 하나를 생성하여 Linked List에 추가하는 함수 (calloc 사용)
/***********************************************************/

#if 0

SCORE* Create_Node(SCORE* d)
{
	SCORE* p;

	p = (SCORE*)calloc(1, sizeof(SCORE));
	if (p == (SCORE*)0) return p; // ?
	*p = *d;

	p->parent = p->left = p->right = (SCORE*)0;
	return p;
}

int Insert_Node(SCORE* head, SCORE* d) // head는 root 주소
{
	SCORE* newnode = Create_Node(d);
	if (newnode == (SCORE*)0) return -1;

	if (head == (SCORE*)0) { // 아무 노드도 없을 때
		Root = newnode;
	}
	else {
		SCORE* parent = head; // 새로운 노드를 연결시킬 부모를 찾자. head부터 탐색 시작
		while (parent) {
			if (parent->id == newnode->id) {
				free(newnode);
				return -2; // 할당받은 것 반납해야함
			}
			else if (parent->id > newnode->id) {
				if (parent->left) parent = parent->left;
				else {
					parent->left = newnode; // 왼쪽 자식이 없다.
					newnode->parent = parent; // 자식도 부모를 연결해주어야함
					break;
				}
			}
			else {
				if (parent->right) parent = parent->right;
				else {
					parent->right = newnode; // 오른쪽 자식이 없다.
					newnode->parent = parent;
					break;
				}
			}
		}
	}
}

#endif

#if 0

void main(void)
{
	int i;
	int r;

	for (i = 0; i < MAX_ST; i++)
	{
		printf("[Loop: %d] Insert Node Result=%d, ID=%d\n", i, r = Insert_Node(Root, &test[i]), test[i].id);
		Print_All_Node(Root);
	}
}

#endif

/***********************************************************/
// [2-3-4.4] 주어진 사번의 node를 찾아서 노드의 주소를 리턴하는 함수
/***********************************************************/

#if 0

SCORE* Search_Node(SCORE* head, int id)
{
	SCORE* node = head;

	while (node) {
		if (node->id == id) return node;
		else if (node->id > id) node = node->left;
		else node = node->right;
	}
	return (SCORE*)0;
}

#endif

#if 0

void main(void)
{
	int i;
	int r;
	SCORE* p;

	for (i = 0; i < 8; i++)
	{
		printf("[Loop: %d] Insert Node Result=%d, ID=%d\n", i, r = Insert_Node(Root, &test[i]), test[i].id);
	}

	Print_All_Node(Root);

	printf("Search Result = 0x%.8X\n", p = Search_Node(Root, 1));
	if (p) 	printf("addr=0x%.8X, ID=%d, left=0x%.8X, right=0x%.8X, parent=0x%.8X\n", p, p->id, p->left, p->right, p->parent);

	printf("Search Result = 0x%.8X\n", p = Search_Node(Root, 10));
	if (p)  printf("addr=0x%.8X, ID=%d, left=0x%.8X, right=0x%.8X, parent=0x%.8X\n", p, p->id, p->left, p->right, p->parent);

	printf("Search Result = 0x%.8X\n", p = Search_Node(Root, 9));
	if (p) 	printf("addr=0x%.8X, ID=%d, left=0x%.8X, right=0x%.8X, parent=0x%.8X\n", p, p->id, p->left, p->right, p->parent);

	printf("Search Result = 0x%.8X\n", p = Search_Node(Root, 4));
	if (p) 	printf("addr=0x%.8X, ID=%d, left=0x%.8X, right=0x%.8X, parent=0x%.8X\n", p, p->id, p->left, p->right, p->parent);

	printf("Search Result = 0x%.8X\n", p = Search_Node(Root, 7));
	if (p) 	printf("addr=0x%.8X, ID=%d, left=0x%.8X, right=0x%.8X, parent=0x%.8X\n", p, p->id, p->left, p->right, p->parent);
}


#endif

/***********************************************************/
// [2-3-4.5] 주어진 사번의 node를 찾아서 삭제하는 함수
/***********************************************************/

#if 0

void Delete_All_Node(SCORE* p)
{ // Post Order로 삭제
	if (p->left) Delete_All_Node(p->left);
	if (p->right) Delete_All_Node(p->right);
	if (p == Root) Root = (SCORE*)0;
	free(p);
}

#endif

#if 0

// 삭제할 대상 노드가 leaf인 경우 삭제 함수
// main 함수에서 "자식 없는 노드의 삭제" 부분만 실험

int Delete_Node(SCORE* head, int id)
{
	SCORE* r;

	r = Search_Node(head, id);

	// 탐색 실패
	if (r == NULL) return -1;

	// 삭제할 노드가 leaf ��� ������ Root�� ��� Root�� NULL ����
	// Root�� �ƴϸ� ���� ��带 �����ϰ� �ִ� �θ��� left �Ǵ� right�� NULL ����







	free(r);
	return 1;
}

#endif

#if 0

// ������ ��� ��尡 leaf �Ǵ� �ڽ��� �ϳ��� ��� ���� �Լ�
// main �Լ����� "�ڽ� ���� ����� ����" �κа� "�ڽ��� 1�� ����� ����" ���� ����

int Delete_Node(SCORE* head, int id)
{
	SCORE* r;
	SCORE* next;

	r = Search_Node(head, id);

	// Ž�� ����
	if (r == NULL) return -1;

	// [1] �İ��� ����
	// leaf�̸� next�� NULL
	// �ڽ��� �ϳ��� ������ ����� left �Ǵ� right�� �����ϴ� �İ��� �ּҸ� next�� ����
	// �ڽ��� �ϳ��� NULL�� �ƴ� r->left �Ǵ� r->right�� �����Ѵ�





	// [2] �ڽ��� �ϳ� �ִ� ����� �İ��� parent�� ������ ����� �θ�� ����
	// �İ����� parent ��(next->parent)�� ������ ����� parent ��(r->parent)�� ����





	// [3] ������ ����� �θ��� left �Ǵ� right�� �İ��� ����
	// ������ ��尡 leaf ��� ������ Root�� ��� Root�� �İ��� �ּ�(next) ����
	// Root�� �ƴϸ� ���� ��带 �����ϰ� �ִ� �θ��� left �Ǵ� right�� �İ��� �ּ�(next) ����
	// leaf�� ���� �İ��ڿ� NULL�� �����Ͽ� �ξ����Ƿ� ������ �����Ͽ� �ۼ��� �ʿ䰡 ����






	free(r);
	return 1;
}

#endif

#if 0

// ������ ��� ��尡 �ڽ� �� �� ������ �����ϴ� ���� ���� �Լ�
// main �Լ����� ��� �ܰ踦 ���� �ǽ�

int Delete_Node(SCORE* head, int id)
{
	// �İ��� ���� ����
	SCORE* next;
	SCORE* r;

	r = Search_Node(head, id);
	if (r == NULL) return -1;

	// �ڽ��� ���̸� �İ��� Ž�� �� �İ��ڸ� ������ ����� �����Ϳ� �����ϰ� ���������� r�� �İ��� �ּ� ����
	if ((r->left != NULL) && (r->right != NULL))
	{
		// �ʿ�� �������� �����Ӱ� �����Ͽ� ���
		// �İ��� ������ ������ ��忡 ������ �� parent, left, right�� ���� ���� ����� ���� �����ؾ� �Ѵ�
		// �� ��ũ���� �״�� �����ϰ� ������ ������ �����Ͽ��� �Ѵ�







	}

	// �ڽ��� ���̸� r�� ������ ��� �ּҰ� ����Ǿ� �ְ� �ϳ��ų� leaf�̸� ó������ ���� ����� ��� ����
	// ���� �Ʒ� �ڵ�� �ڽ� ���� �����ϰ� ������

	// �İ��� ����
	// �ڽ��� �ϳ��� ��� ��� ���� �ڽ��� �ִ����� ã�Ƽ� �ڽ��� next�� �����Ѵ�
	// leaf�̸� �İ��ڴ� NULL�� ����(��, ������ leaf�̸� r-> left�� r->right�� NULL�̴�)
	if (r->left) next = r->left;
	else next = r->right;

	// �İ��ڰ� ���� ��� �İ�����parent = ���� ����� parent ����
	if (next) next->parent = r->parent;

	// ���� ����� Root�� �ƴ� ��� ���� ��� ����� parent�� �İ��ڸ� �����Ѵ�(leaf�̸� NULL�� ���Եȴ�)
	if (r != Root)
	{
		// ���� ��� ��尡 �θ��� left���� right������ ���� �θ��� left�� rght�� �İ��ڸ� �����Ѵ�
		if (r == r->parent->left) r->parent->left = next;
		else  r->parent->right = next;
	}

	// ������ ��尡 Root�� ��� �İ��ڸ� Root�� ����(leaf�̸� NULL�� ���Եȴ�)
	else
	{
		Root = next;
	}

	free(r);
	return 1;
}

#endif

#if 0

SCORE* Find_Successor(SCORE* delnode) { // left 중 가장 큰 것
	SCORE* successor = delnode->left;
	while (successor->right) successor = successor->right;

	return successor;
	/* right 중 가장 작은 것
	SCORE* successor = delnode->right;
	while (successor->left) successor = successor->left;
	return successor;
	*/
}

void _Delete_Node(SCORE* delnode) { // 주소를 받은 이상 삭제 실패라는 것은 없으므로 void
	// 자식 수부터 확인
	int cnt_child = 0;
	SCORE* child;
	SCORE* successor;
	if (delnode->left) cnt_child++;
	if (delnode->right) cnt_child++;

	switch (cnt_child){
	case 0: // 자식이 0개
		if (delnode->parent == (SCORE*)0) { // delnode가 root인 상황
			Root = (SCORE*)0;
		}
		else {
			if(delnode->parent->left == delnode) delnode->parent->left = (SCORE*)0; // 삭제할 노드가 왼쪽 자식이었다.
			else delnode->parent->right = (SCORE*)0;
		}
		free(delnode);
		break;
	case 1: // 자식을 부모에게 맡기자.
		child = delnode->left ? delnode->left : delnode->right; // 왼쪽이 존재하면 왼쪽, 오른쪽이 존재하면 오른쪽
		if (delnode->parent == (SCORE*)0) { // delnode가 root인 상황
			Root = child;
			child->parent = (SCORE*)0;
		}
		else {
			child->parent = delnode->parent; // 지울 노드의 자식의 부모를 지울 노드의 부모로
			if (delnode->parent->left == delnode) delnode->parent->left = child; // 지울 노드가 부모의 왼쪽 자식이었다면, 지울 노드의 자식을 부모의 왼쪽 자식으로
			else delnode->parent->right = child;
		}
		free(delnode);
		break;
	case 2:
		successor = Find_Successor(delnode); // 후계자 찾기
		delnode->id = successor->id; // 연결 관계를 뺀 data만 복사
		strcpy(delnode->name, successor->name);
		delnode->jumsu = successor->jumsu;
		// 후보자 노드 정리
		_Delete_Node(successor);
		break;
	}
}

int Delete_Node(SCORE* head, int id)
{
	SCORE* delnode = Search_Node(head, id);
	if (delnode == (SCORE*)0) return -1; // 탐색 실패

	_Delete_Node(delnode); // 실제 삭제하는 함수

	return 1;
}

#endif

#if 0

void main(void)
{
	int i;
	int r;

	/* 자식 없는 노드의 삭제 */

#if 0

	// 1. Root Only 삭제

	printf("[Loop: %d] Insert Node Result=%d, ID=%d\n", 0, r = Insert_Node(Root, &test[0]), test[0].id);
	Print_All_Node(Root);
	printf("Delete Node #10 Result = %d\n", Delete_Node(Root, 10));
	printf("Root=%#.8x\n", Root);
	Print_All_Node(Root);

#endif

#if 0

	// 2. Left Leaf 노드 삭제

	for (i = 0; i < 7; i++) printf("[Loop: %d] Insert Node Result=%d, ID=%d\n", i, r = Insert_Node(Root, &test[i]), test[i].id);
	Print_All_Node(Root);
	printf("Delete Node #3 Result = %d, Root = %d\n", Delete_Node(Root, 3), Root->id);
	printf("Delete Node #1 Result = %d, Root = %d\n", Delete_Node(Root, 1), Root->id);
	Print_All_Node(Root);
	Delete_All_Node(Root);

#endif

#if 0

	// 3. Right Leaf 노드 삭제

	for (i = 0; i < 20; i++) printf("[Loop: %d] Insert Node Result=%d, ID=%d\n", i, r = Insert_Node(Root, &test[i]), test[i].id);
	Print_All_Node(Root);
	printf("Delete Node #13 Result = %d, Root = %d\n", Delete_Node(Root, 13), Root->id);
	printf("Delete Node #9 Result = %d, Root = %d\n", Delete_Node(Root, 9), Root->id);
	Print_All_Node(Root);
	Delete_All_Node(Root);

#endif

	/* 자식이 1인 노드 삭제 */

#if 0

	// 1. Left만 있는 Root 삭제

	for (i = 0; i < 10; i++) printf("[Loop: %d] Insert Node Result=%d, ID=%d\n", i, r = Insert_Node(Root, &test[i]), test[i].id);
	Print_All_Node(Root);
	printf("Delete Node #10 Result = %d, Root = %d\n", Delete_Node(Root, 10), Root->id);
	Print_All_Node(Root);
	Delete_All_Node(Root);

#endif

#if 0

	// 2. Right만 있는 Root 삭제

	printf("[Loop: %d] Insert Node Result=%d, ID=%d\n", 0, r = Insert_Node(Root, &test[0]), test[0].id);
	for (i = 10; i < 20; i++) printf("[Loop: %d] Insert Node Result=%d, ID=%d\n", i, r = Insert_Node(Root, &test[i]), test[i].id);
	Print_All_Node(Root);
	printf("Delete Node #10 Result = %d, Root = %d\n", Delete_Node(Root, 10), Root->id);
	printf("Delete Node #8 Result = %d, Root = %d\n", Delete_Node(Root, 8), Root->id);
	Print_All_Node(Root);
	Delete_All_Node(Root);

#endif

#if 0

	// 3. Left�� �ִ� ��� ����

	for (i = 0; i < 20; i++) printf("[Loop: %d] Insert Node Result=%d, ID=%d\n", i, r = Insert_Node(Root, &test[i]), test[i].id);
	Print_All_Node(Root);
	printf("Delete Node #7 Result = %d, Root = %d\n", Delete_Node(Root, 7), Root->id);
	printf("Delete Node #19 Result = %d, Root = %d\n", Delete_Node(Root, 19), Root->id);
	printf("Delete Node #14 Result = %d, Root = %d\n", Delete_Node(Root, 14), Root->id);
	Print_All_Node(Root);
	Delete_All_Node(Root);

#endif

#if 0

	// 4. Right�� �ִ� ��� ����

	for (i = 0; i < 20; i++) printf("[Loop: %d] Insert Node Result=%d, ID=%d\n", i, r = Insert_Node(Root, &test[i]), test[i].id);
	Print_All_Node(Root);
	printf("Delete Node #5 Result = %d, Root = %d\n", Delete_Node(Root, 5), Root->id);
	printf("Delete Node #12 Result = %d, Root = %d\n", Delete_Node(Root, 12), Root->id);
	printf("Delete Node #11 Result = %d, Root = %d\n", Delete_Node(Root, 11), Root->id);
	Print_All_Node(Root);
	Delete_All_Node(Root);

#endif

	/* 자식이 2인 노드 삭제  */

#if 0

	// 1. Root 삭제

	for (i = 0; i < 20; i++) printf("[Loop: %d] Insert Node Result=%d, ID=%d\n", i, r = Insert_Node(Root, &test[i]), test[i].id);
	Print_All_Node(Root);
	printf("Delete Node #10 Result = %d, Root = %d\n", Delete_Node(Root, 10), Root->id);
	Print_All_Node(Root);
	Delete_All_Node(Root);

#endif

#if 0

	// 2. �߰� ��� ����

	for (i = 0; i < 20; i++) printf("[Loop: %d] Insert Node Result=%d, ID=%d\n", i, r = Insert_Node(Root, &test[i]), test[i].id);
	Print_All_Node(Root);
	printf("Delete Node #2 Result = %d, Root = %d\n", Delete_Node(Root, 2), Root->id);
	Print_All_Node(Root);
	printf("Delete Node #15 Result = %d, Root = %d\n", Delete_Node(Root, 15), Root->id);
	Print_All_Node(Root);
	printf("Delete Node #3 Result = %d, Root = %d\n", Delete_Node(Root, 3), Root->id);
	Print_All_Node(Root);
	printf("Delete Node #4 Result = %d, Root = %d\n", Delete_Node(Root, 4), Root->id);
	Print_All_Node(Root);
	Delete_All_Node(Root);

#endif
}

#endif

#endif


/*
[삭제에서 사용되는 트리 구조]
									10
							2						15
						1		8			11			17
							4		9			14	16		20
						3			


*/