/* map, iteratorO */
#include<map>
using namespace std;
using pii = pair<int, int>;

int n;
map<int, pii> ladder[103];				// ladder[x][y] = { connected x, connected iterator id }
map<int, pii>::iterator iter[400003];	// iter[n] = n��° ������ iterator

void init() {
	for (int i = 1; i <= 100; i++) ladder[i].clear();
	n = 0;
}

void add(int x, int y) {
	iter[n + 1] = ladder[x].insert({ y, {x + 1, n } }).first;	// �� iteartor ��ȣ�� n+1
	iter[n] = ladder[x + 1].insert({ y, {x, n + 1 } }).first;	// �� iteartor ��ȣ�� n
	n += 2;
}

void remove(int x, int y) {
	auto it = ladder[x].find(y);
	ladder[x + 1].erase(iter[it->second.second]);
	ladder[x].erase(it);
}

int getCrossCnt(int lineID) {
	int cnt = 0, x = lineID;
	auto it = ladder[x].begin();
	while (it != ladder[x].end()) {
		cnt++;
		x = it->second.first;					// ����� x
		it = next(iter[it->second.second]);		// next(����� node�� iterator)
	}
	return cnt;
}

int getLineID(int x, int y) {
	auto it = ladder[x].lower_bound(y);
	while (it != ladder[x].begin()) {
		--it;
		x = it->second.first;
		it = iter[it->second.second];
	}
	return x;
}