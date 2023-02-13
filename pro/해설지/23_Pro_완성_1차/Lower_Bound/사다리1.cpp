/* map, iteratorX */
#include <map>
using namespace std;

map<int, int> ladder[103];		// ladder[x][y] = connected x

void init() {
	for (int i = 1; i <= 100; i++) ladder[i].clear();
}

void add(int x, int y) {
	ladder[x][y] = x + 1;
	ladder[x + 1][y] = x;
}

void remove(int x, int y) {
	ladder[x].erase(y);
	ladder[x + 1].erase(y);
}

int getCrossCnt(int lineID) {
	int cnt = 0, x = lineID;
	auto it = ladder[x].begin();
	while (it != ladder[x].end()) {
		cnt++;									
		x = it->second;
		it = ladder[x].upper_bound(it->first);
	}
	return cnt;
}

int getLineID(int x, int y) {
	auto it = ladder[x].lower_bound(y);
	while (it != ladder[x].begin()) {
		--it;
		x = it->second;
		it = ladder[x].find(it->first);
	}
	return x;
}