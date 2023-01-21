'''
그룹 인원 적은 쪽에서 많은 쪽으로 전부 이동
'''
def init(N):
    global gid, gScore, score, group
    gid = [i for i in range(N+1)]
    gScore = [0] * (N+1)
    score = [0] * (N+1)
    group = [[i] for i in range(N+1)]

def updateScore(mWinnerID, mLoserID, mScore):
    gScore[gid[mWinnerID]] += mScore
    gScore[gid[mLoserID]] -= mScore

def unionTeam(mPlayerA, mPlayerB):
    a, b = gid[mPlayerA], gid[mPlayerB]
    if len(group[a]) < len(group[b]): a,b = b,a

    for x in group[b]:
        score[x] += gScore[b]-gScore[a]
        gid[x] = a
        group[a].append(x)

def getScore(mID):
    return score[mID] + gScore[gid[mID]]