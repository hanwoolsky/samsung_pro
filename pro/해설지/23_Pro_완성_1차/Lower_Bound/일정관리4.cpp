#define MAXL		(11)

struct RESULT
{
	char mTitle[MAXL];
	int mStartDay;
	int mEndDay;
};

#include<map>
#include<string>
#include<string.h>
#include<algorithm>
#include<unordered_map>
using namespace std;
using pii = pair<int, int>;

map<pii, string> M;					// M[{end, start}] = title
unordered_map<string, map<pii, string>::iterator> hmap;	// hmap[title] = M iterator

void init(int N)
{
	hmap.clear();
	M.clear();
	M[{0, 0}], M[{N + 1, N + 1}];
}

int addSchedule(char mTitle[], int mStartDay, int mEndDay, int mForced)
{
	auto it = M.lower_bound({ mStartDay, 0 });		// mStartDay 포함 그 이후에 끝나는 가장 빠른 일정
	// it->first = {end, start}	| it->second = title
	if (!mForced)
		if (it->first.second <= mEndDay) return 0;

	if (mForced) {
		while (it->first.second <= mEndDay) {		// 여러개 겹칠 수 있음
			hmap.erase(it->second);
			it = M.erase(it);
		}
	}

	hmap[mTitle] = M.insert({ {mEndDay, mStartDay}, mTitle }).first;
	return 1;
}

RESULT getSchedule(int mDay)
{
	RESULT ret = {};
	auto it = M.lower_bound({ mDay, 0 });
	if (it->first.second <= mDay) {
		strcpy(ret.mTitle, it->second.c_str());
		ret.mStartDay = it->first.second;
		ret.mEndDay = it->first.first;
	}
	return ret;
}

int deleteSchedule(char mTitle[])
{
	if (!hmap.count(mTitle)) return 0;
	M.erase(hmap[mTitle]);
	hmap.erase(mTitle);
	return 1;
}

int findEmptySchedule()
{
	int ret = 0;
	for (auto l = M.begin(), r = ++M.begin(); r != M.end(); ++l, ++r)
		// 빈 일정 길이 = (오른쪽 일정 시작 - 왼쪽 일정 끝 - 1)
		ret = max(ret, r->first.second - l->first.first - 1);
	return ret;
}