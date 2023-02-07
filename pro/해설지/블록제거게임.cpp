/*
* 연속된 block을 하나의 노드로 관리		: linked list, 1)시간 2)열오름차순 관리
* 연속된 removal를 하나의 노드로 관리	: linked list, 열오름차순 관리
*/
#include<list>
using namespace std;

int R, C, total;
struct Data { int t, s, e; };
list<Data> block;

void init(int r, int c) {
	R = r, C = c, total = 0;
	block.clear();
}

void update(int timestamp) {
	while (block.size()) {
		auto it = block.begin();			// 가장 먼저 들어온 블록 선택
		if (timestamp - it->t < R) break;	// 아직 맵에서 안벗어난 경우 종료

		total -= it->e - it->s + 1;			// 개수 업데이트 후,
		block.erase(it);					// 맵에서 제거
	}
}

int dropBlocks(int timestamp, int col, int len) {
	update(timestamp);
	block.push_back({ timestamp, col, col+len-1 });
	total += len;
	return total;
}


// li의 it 노드의 시작=my_s, 끝=my_e
// 겹치는 구간 시작=s, 끝=e
template<typename T, typename U>
void remove(T&li, U&it, int s, int e) {
	int my_s = it->s, my_e = it->e;

	/* 완전히 포함되어 전부 삭제되는 경우 */
	if (s == my_s && my_e == e)
		it = li.erase(it);

	/* 완전히 포함하여 양쪽 두개로 분리되는 경우 */
	else if (my_s < s && e < my_e) {
		it->s = e + 1;
		li.insert(it, { it->t, my_s, s-1 });
	}

	/* 오른쪽만 남는 경우 */
	else if (my_s == s)				// my_s == s && e < my_e
		it->s = e + 1;

	/* 왼쪽만 남는 경우 */
	else {							// my_s < s && my_e==e
		it->e = s - 1;
		++it;
	}
}

int removeBlocks(int timestamp) {
	update(timestamp);
	list<Data> removal = { {0,0,C - 1} };		// 지워야하는 구간(t는 의미없음)
	auto rit = removal.begin();
	auto bit = block.begin();
	while(bit != block.end()) {
		int t = bit->t, bs = bit->s, be = bit->e;
		
		if (rit == removal.end()) ++bit;	// removal가 bit 이전 앞쪽에서 끝난 경우
		else {
			int rs = rit->s, re = rit->e;

			/* 블록이 오른쪽으로 치우쳐 안겹치는 경우 */
			if (re < bs) ++rit;

			/* 블록이 왼쪽으로 치우쳐 안겹치는 경우 */
			else if (be < rs) ++bit;

			/* 겹치는 경우 */
			else {
				int s = max(bs, rs), e = min(be, re);
				total -= e - s + 1;
				remove(block, bit, s, e);
				remove(removal, rit, s, e);
			}
		}

		/* 새로운 라인의 블록이 설정된 경우 */
		if (bit != block.end() && bit->t != t) rit = removal.begin();
	}
	
	return total;
}