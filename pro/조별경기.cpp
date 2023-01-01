const int SIZE = 100001;
int parent[SIZE];
int score[SIZE];

int find(int x){
  if(x == parent[x]){
    return x;
  }
  int root = find(parent[x]);

  if(root != parent[x]){
    score[x] += score[parent[x]];
    parent[x] = root;
  }
  return root;
}

void init(int N)
{
  for(int i = 1; i <= N; i++){
    parent[i] = i;
    score[i] = 0;
  }
}

void updateScore(int mWinnerID, int mLoserID, int mScore)
{
  int winner = find(mWinnerID);
  int loser = find(mLoserID);

  score[winner] += mScore;
  score[loser] -= mScore;
}

void unionTeam(int mPlayerA, int mPlayerB)
{
  int team1 = find(mPlayerA);
  int team2 = find(mPlayerB);

  parent[team1] = team2;
  score[team1] -= score[team2];
}

int getScore(int mID)
{
  int root = find(mID);
  if(mID == root){
    return score[mID];
  }
	return score[mID] + score[root];
}
