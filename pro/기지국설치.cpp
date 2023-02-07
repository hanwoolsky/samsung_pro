// 2036ms
#include <unordered_map>
#include <set>
#include <algorithm>
using namespace std;

unordered_map<int, int> idToLoc;
unordered_map<int, int> locToId;
set<int> loc;

int buildNum;

void init(int N, int mId[], int mLocation[]) {
	buildNum = N;
    idToLoc.clear(); locToId.clear(); loc.clear();
	for (int i = 0; i < N; i++) {
		idToLoc.insert({ mId[i], mLocation[i] });
		locToId.insert({ mLocation[i], mId[i] });
		loc.insert(mLocation[i]);
	}
}

int add(int mId, int mLocation) {
	auto it = idToLoc.find(mId);
	if (it != idToLoc.end()) {
		locToId.erase(idToLoc[mId]);
		loc.erase(idToLoc[mId]);
		idToLoc[mId] = mLocation;
		loc.insert(mLocation);
		locToId.insert({ mLocation, mId });
	}
	else {
		idToLoc.insert({ mId, mLocation });
		locToId.insert({ mLocation, mId });
		loc.insert(mLocation);
		buildNum++;
	}
	return buildNum;
}

int remove(int mStart, int mEnd) {
	auto sit = loc.lower_bound(mStart);
	auto eit = loc.lower_bound(mEnd);
	if (sit == loc.end()) return buildNum;
	if(eit != loc.end() && *eit == mEnd) eit++;

	for (auto it = sit; it != eit;) {
		idToLoc.erase(locToId[*it]);
		locToId.erase(*it);
		it = loc.erase(it);
		buildNum--;
	}

	return buildNum;
}

bool possible(int len, int cnt) {
	auto newLoc = loc.begin();

	cnt--;
	while (cnt--) {
		newLoc = loc.lower_bound(*newLoc + len);
		if (newLoc == loc.end()) return 0;
		if (newLoc == --loc.end() && cnt == 1) return 0;
	}
	return 1;
}

int install(int M) {
	int firstLoc = *loc.begin(); // 가장 첫 번째 위치
	int lastLoc = *(--loc.end()); // 가장 마지막 위치

	int maxLen = 1;
	int s = 1, e = (lastLoc - firstLoc) / (M - 1) + firstLoc;
	while (s <= e) {
		int mid = (s + e) / 2;
		if (possible(mid, M)) {
			maxLen = max(mid, maxLen);
			s = mid + 1;
		}
		else e = mid - 1;
	}

	return maxLen;
}

// 373ms
// 2036ms
#include <unordered_map>
#include <set>
#include <algorithm>
using namespace std;

unordered_map<int, int> idToLoc;
unordered_map<int, int> locToId;
set<int> loc;

int buildNum;
int setArr[25000];

void init(int N, int mId[], int mLocation[]) {
	buildNum = N;
	idToLoc.clear(); locToId.clear(); loc.clear();
	for (int i = 0; i < N; i++) {
		idToLoc.insert({ mId[i], mLocation[i] });
		locToId.insert({ mLocation[i], mId[i] });
		loc.insert(mLocation[i]);
	}
}

int add(int mId, int mLocation) {
	auto it = idToLoc.find(mId);
	if (it != idToLoc.end()) {
		locToId.erase(idToLoc[mId]);
		loc.erase(idToLoc[mId]);
		idToLoc[mId] = mLocation;
		loc.insert(mLocation);
		locToId.insert({ mLocation, mId });
	}
	else {
		idToLoc.insert({ mId, mLocation });
		locToId.insert({ mLocation, mId });
		loc.insert(mLocation);
		buildNum++;
	}
	return buildNum;
}

int remove(int mStart, int mEnd) {
	auto sit = loc.lower_bound(mStart);
	auto eit = loc.lower_bound(mEnd);
	if (sit == loc.end()) return buildNum;
	if (eit != loc.end() && *eit == mEnd) eit++;

	for (auto it = sit; it != eit;) {
		idToLoc.erase(locToId[*it]);
		locToId.erase(*it);
		it = loc.erase(it);
		buildNum--;
	}

	return buildNum;
}

int install(int M) {
	int low = (int)1e9, mid, high;
	int i, ans, len = 0;
	for (auto& p : loc) // 위치값만 임시배열 setArr[]에 복사 : set이므로 정렬된 상태로 복사됨.
		setArr[++len] = p;
	for (i = 2; i <= len; ++i) // 답으로 가능한 범위의 최소값 구하기
		low = min(low, setArr[i] - setArr[i - 1]);
	ans = high = setArr[len] - setArr[1]; // 답으로 가능한 범위의 최대값 구하기
	while (low <= high) { // 이진 탐색
		mid = (low + high) / 2;
		int cnt = 1, latest = setArr[1]; // 첫 위치에 기지국 놓고 시작
		for (i = 2; i <= len; ++i) {
			if (setArr[i] - latest >= mid) // 답으로 가정한 ans보다 거리가 늘어나는 경우
				cnt++, latest = setArr[i]; // 새로운 기지국 설치
		}
		if (cnt >= M) // 답으로 가능한 경우 ans 업데이트: 더 큰 범위로 조정
			ans = mid, low = mid + 1;
		else high = mid - 1; // 답으로 불가능한 경우 : 더 작은 범위로 조정
	}
	return ans;
}
