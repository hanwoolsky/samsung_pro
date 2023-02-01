#include <cstring>
using namespace std;
#define SIZE 100000

int parent[SIZE + 1];
int score[SIZE + 1];

int find(int x) {
	if (x == parent[x]) return x;

	int root = find(parent[x]);
	if (root != parent[x]) {
		score[x] += score[parent[x]];
		parent[x] = root;
	}
	return root;
}

void init(int N) {
	memset(score, 0, sizeof(score));
	for (int i = 1; i <= N; i++) {
		parent[i] = i;
	}
}

void updateScore(int mWinnerID, int mLoserID, int mScore){
	score[find(mWinnerID)] += mScore;
	score[find(mLoserID)] -= mScore;
}

void unionTeam(int mPlayerA, int mPlayerB){
	int rootA = find(mPlayerA);
	int rootB = find(mPlayerB);

	parent[rootB] = rootA;
	score[rootB] -= score[rootA];
}

int getScore(int mID){
	int root = find(mID);

	if (root == mID) return score[root];
	return score[mID] + score[root];
}