'''
union-find (path compression + union by rank)
'''
def init(N):
    global parent, rank, score
    parent = [i for i in range(N+1)]
    rank = [0] * (N+1)
    score = [0] * (N+1)

def find(x):
    if x==parent[x]: return x

    root = find(parent[x])
    if root != parent[x]:
        score[x] += score[parent[x]]
        parent[x] = root
    return root

def updateScore(mWinnerID, mLoserID, mScore):
    score[find(mWinnerID)] += mScore
    score[find(mLoserID)] -= mScore

def unionTeam(mPlayerA, mPlayerB):
    a, b = find(mPlayerA), find(mPlayerB)
    if rank[a] < rank[b]: a,b = b,a
    parent[b] = a
    score[b] -= score[a]
    if rank[a]==rank[b]: rank[a]+=1

def getScore(mID):
    root = find(mID)
    return score[mID] if root==mID else score[mID]+score[root]