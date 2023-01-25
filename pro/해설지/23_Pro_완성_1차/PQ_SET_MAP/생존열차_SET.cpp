#include<set>
#include<vector>
#include<string.h>
using namespace std;
using pii = pair<int, int>;

set<pii> s[10];						// {-point, id}	, begin() : 최상위 , rbegin() : 최하위
set<pii>::iterator iter[100003];

int carCnt;							// 칸 개수
int car[100003];					// tid[uID] = uID 회원이 탑승한 칸
int point[100003];					// point[uID] = uID 회원의 포인트

vector<int> joblist[1003];			// joblist[jobID] = { jobID 직업의 탑승객 리스트 }

void init(int N, int M, int J, int Point[], int JobID[])
{
	carCnt = N / M;
	for (int i = 0; i < J; i++) joblist[i].clear();
	for (int i = 0; i < carCnt; i++) s[i].clear();

	for (int i = 0; i < N; i++) {
		point[i] = Point[i];
		joblist[JobID[i]].push_back(i);

		car[i] = i / M;
		iter[i] = s[i / M].insert({ -point[i], i }).first;
	}
}

void destroy() {}

void update(int x) {
	s[car[x]].erase(iter[x]);
	iter[x] = s[car[x]].insert({ -point[x], x }).first;
}

int update(int uID, int Point)
{
	point[uID] += Point;
	update(uID);
	return point[uID];
}

int updateByJob(int JobID, int Point)
{
	int ret = 0;
	for (int x : joblist[JobID]) {
		point[x] += Point;
		update(x);
		ret += point[x];
	}
	return ret;
}

int move(int num)
{
	vector<int> a[10];	// a[cID] = { cID 칸으로 옮겨지는 탑승객 uID 리스트 }
	int ret = 0;
	for (int i = 1; i < carCnt; i++) {		// 이동하는 탑승객 a에 저장, set에서 제거
		for (int j = 0; j < num; j++) {
			a[i].push_back(s[i - 1].rbegin()->second);
			a[i - 1].push_back(s[i].begin()->second);
			s[i - 1].erase(--s[i - 1].end());
			s[i].erase(s[i].begin());
		}
	}
	for (int i = 0; i < carCnt; i++) {		// 이동하는 칸으로 set에 등록
		for (int x : a[i]) {
			car[x] = i;
			iter[x] = s[i].insert({ -point[x], x }).first;
			ret += point[x];
		}
	}
	return ret;
}