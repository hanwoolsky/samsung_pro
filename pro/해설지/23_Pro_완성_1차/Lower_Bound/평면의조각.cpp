#include<vector>
#include<algorithm>
using namespace std;
using pii = pair<int, int>;
vector<pii> L[3];		// { value, id }

void init(int N, int ID[100000], int type[100000], int X[100000], int Y[100000])
{
	for (auto&v : L) v = { {-(int)1e9,0}, {(int)1e9,0} };
	for (int i = 0; i < N; i++) {
		if (type[i] == 0) L[0].push_back({ Y[i], ID[i] });			// value = y
		if (type[i] == 1) L[1].push_back({ X[i], ID[i] });			// value = x
		if (type[i] == 2) L[2].push_back({ Y[i] - X[i], ID[i] });	// value = y - x
	}
	for (auto&v : L) sort(v.begin(), v.end());
}

int findPiece(int interiorX, int interiorY)
{
	int ret = 0;

	auto yit = lower_bound(L[0].begin(), L[0].end(), pii{ interiorY,0 });				// 수평라인
	auto xit = lower_bound(L[1].begin(), L[1].end(), pii{ interiorX,0 });				// 수직라인
	auto dit = lower_bound(L[2].begin(), L[2].end(), pii{ interiorY - interiorX,0 });	// 대각라인

	int ex = xit->first,		exid = xit->second;				// rig	ht
	int sx = (--xit)->first,	sxid = xit->second;				// left
	int ey = yit->first,		eyid = yit->second;				// top
	int sy = (--yit)->first,	syid = yit->second;				// bottom
	
	int value = dit->first, id = dit->second;					// 위 대각라인
	if (value + sx < ey) ret += id;
	if (value + sx > sy) ret += sxid;
	if (value + ex > ey) ret += eyid;

	value =(--dit)->first, id = dit->second;					// 아래 대각라인
	if (value + ex > sy) ret += id;
	if (value + ex < ey) ret += exid;
	if (value + sx < sy) ret += syid;

	return ret;
}