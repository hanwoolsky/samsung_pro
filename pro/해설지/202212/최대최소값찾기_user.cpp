/*
* 전체로 관리하며 max, min값 미리 구해놓기
*/
#include<algorithm>
using namespace std;

const int LM = 200003;
int N;
int A[LM];
int minA[LM];       // minA[i] = i~N-1 까지 값 중 최소값
int maxA[LM];       // maxA[i] = i~N-1 까지 값 중 최대값

void init(int N, int val[]) {
	::N = N;
	minA[N] = 1e9, maxA[N] = -1;
	for (int i = N - 1; i >= 0; i--) {          // 뒤에서부터 A,min,max 업데이트
		A[i] = val[i];
		minA[i] = min(minA[i + 1], A[i]);
		maxA[i] = max(maxA[i + 1], A[i]);
	}
}

void add(int M, int val[]) {
	minA[N + M] = 1e9, maxA[N + M] = -1;
	for (int i = N + M - 1; i >= N; i--) {      // 뒤에서부터 추가된 값 A,min,max 업데이트
		A[i] = val[i - N];
		minA[i] = min(minA[i + 1], A[i]);
		maxA[i] = max(maxA[i + 1], A[i]);
	}

	/* 기존 원소들 뒤에서부터 min, max 업데이트 */
	for (int i = N - 1; i >= 0; i--) {
		if (minA[i] <= minA[i + 1]) break;      // min값 업데이트 안되는 경우 종료
		minA[i] = minA[i + 1];
	}

	for (int i = N - 1; i >= 0; i--) {
		if (maxA[i] >= maxA[i + 1]) break;      // max값 업데이트 안되는 경우 종료
		maxA[i] = maxA[i + 1];
	}

	N += M;
}

void erase(int s, int e) {
	s--;                                // [s, e) 삭제
	int M = e - s;                      // 삭제되는 원소 개수

	/* 삭제되는 구간 뒤의 원소들 땡겨오기 */
	minA[s] = 1e9, maxA[s] = -1;        // 삭제되는 첫번째 위치 min,max 초기화
	for (int i = e; i < N; i++) {
		A[i - M] = A[i];
		maxA[i - M] = maxA[i];
		minA[i - M] = minA[i];
	}

	/* 삭제되는 구간 앞의 원소들 뒤에서부터 min, max 업데이트 */
	for (int i = s - 1; i >= 0; i--) {
		int maxVal = max(A[i], maxA[i + 1]);
		if (maxA[i] == maxVal) break;               // max값 업데이트 안되는 경우 종료
		maxA[i] = maxVal;
	}

	for (int i = s - 1; i >= 0; i--) {
		int minVal = min(A[i], minA[i + 1]);
		if (minA[i] == minVal) break;               // min값 업데이트 안되는 경우 종료
		minA[i] = minVal;
	}

	N -= M;
}

int find(int K) {
	return maxA[N - K] - minA[N - K];
}