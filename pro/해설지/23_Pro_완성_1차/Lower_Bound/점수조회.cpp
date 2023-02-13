#include<unordered_map>
#include<set>
#include<algorithm>
using namespace std;
using pii = pair<int, int>;

struct Data {
	int grade, gender;
	set<pii>::iterator it;
};
unordered_map<int, Data> hmap;	// hmap[id] = { grade(1,2,3), gender(0,1), set iterator }
set<pii> priority[4][2];		// priority[grade][gender] = { score, id }

void init() {
	for (int i = 1; i <= 3; i++) for (int j = 0; j < 2; j++) priority[i][j].clear();
	hmap.clear();
}

int addScore(int id, int grade, char gender[], int score) {
	int a = grade, b = gender[0] == 'm' ? 1 : 0;
	auto it = priority[a][b].insert({ score, id }).first;
	hmap[id] = { a, b, it };
	return priority[a][b].rbegin()->second;
}

int removeScore(int id) {
	if (!hmap.count(id)) return 0;
	Data d = hmap[id];
	priority[d.grade][d.gender].erase(d.it);
	hmap.erase(id);
	return priority[d.grade][d.gender].empty() ? 0 : priority[d.grade][d.gender].begin()->second;
}

int get(int gradeCnt, int grade[], int genderCnt, char gender[][7], int score) {
	pii ret = { 300001, 0 };
	for (int i = 0; i < gradeCnt; i++) for (int j = 0; j < genderCnt; j++) {
		int a = grade[i], b = gender[j][0] == 'm' ? 1 : 0;
		auto it = priority[a][b].lower_bound({ score,0 });
		if (it != priority[a][b].end()) ret = min(ret, *it);
	}
	return ret.second;
}