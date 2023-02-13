/*
* 문자열 앞 세자리를 이용하여 hash table 생성, id를 담아둔다.
*/
#include<unordered_map>
#include<vector>
#include<string.h>
#include<string>
using namespace std;

unordered_map<string, int> hmap;	// hmap[str] = id(0~)		, 순서대로 번호부여
vector<int> V[26 * 26 * 26];		// V[hash] = { id, ... }	, 앞 세자리가 같은 값끼리 분류
char S[50003][10];					// S[id] = str
bool valid[50003];					// valid[id] = 1/0
int head, tail;	

void init()
{
	head = tail = 0;
	for (auto& v : V) v.clear();
	memset(valid, 0, sizeof(valid));
	hmap.clear();
}

int gethash(char* s) {	// 앞 3자리로 hash value 생성 : 26진법(a=0, z=25)
	int hash = 0;
	for (int i = 0; i < 3; i++) hash = hash * 26 + s[i] - 97;
	return hash;
}

void loginID(char str[10])
{
	if (hmap.count(str)) valid[hmap[str]] = 0;
	int id = hmap[str] = tail++;
	valid[id] = 1;
	strcpy(S[id], str);
	V[gethash(str)].push_back(id);
}

int closeIDs(char prefix[10])
{
	int ret = 0;
	int len = strlen(prefix);
	auto&v = V[gethash(prefix)];
	for (int i = 0; i < v.size();) {
		int id = v[i];
		if (strncmp(S[id] + 3, prefix + 3, len - 3)) {	// prefix로 시작하지 않는 경우
			i++;
			continue;
		}
		if (valid[id]) {						// prefix로 시작하는데 유효한 id인 경우
			ret++;
			valid[id] = 0;
			hmap.erase(S[id]);
		}
		v[i] = v.back();						// 유효하든 유효하지 않든 hash table 에서 삭제
		v.pop_back();
	}
	return ret;
}

void connectCnt(int cnt)
{
	while (cnt) {
		int id = head++;			// 먼저들어온 순서대로 대기열에서 삭제
		if (valid[id]) {			// 유효한 경우
			valid[id] = 0;
			hmap.erase(S[id]);
			cnt--;
		}
	}
}

int waitOrder(char str[10])
{
	if (!hmap.count(str)) return 0;
	int destID = hmap[str];
	int ret = 0;
	for (int id = head; id <= destID; id++)
		if (valid[id]) ret++;
	return ret;
}