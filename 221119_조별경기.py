n = int(input())
team = 0

def findTeam(mID):
    return "[mID가 속한 리스트]"
    getTeam(teamNum[mID-1]) = []

def init(): # 초기 설정 1번
    global score, getTeam, teamNum
    score = [0] * n
    getTeam = dict()
    teamNum = [0] * n

def updateScore(mWinnerID, mLoserID, mScore):
    winner = findTeam(mWinnerID)
    lose = findTeam(mLoserID)

    for i in winner:
        score[i] += mScore
    for i in lose:
        score[i] -= mScore

def unionTeam(mPlayerA, mPlayerB):
    team += 1
    teamNum[mPlayerA] = team
    teamNum[mPlayerB] = team

    getTeam[team] = [mPlayerA, mPlayerA]
    print() # A 그룹, B가 그룹, 그룹 합쳐

def getScore(mID):
    return score[mID-1]


getTeam
{1: [1, 2], 2: [3, 4]}

# n조 리스트


# 목표 : o(N) -> o(logN)
# 함수를 하나씩 지우고 돌려보자, 속도가 어디서 느린지 알기 위해서
# reference code 사용


# ======================================== 정답 코드 ========================================
# group별 최신 점수 기록 : key = gid, val = scoreSum
# group별 선수 명단 dict : key = gid, val = [pid, ...]
# 선수별 점수, 그룹 dict : key = pid, val = (score, group id)
from collections import defaultdict
 
 
def init(N):
    global players, groupScore, groupPlayers
    players = dict()
    groupScore = defaultdict(int)
    groupPlayers = defaultdict(list)
    for i in range(N):
        pid = i+1
        gid = i+1
        players[pid] = [0, gid]
        groupScore[gid] = 0
        groupPlayers[gid].append(pid)
 
 
 
def updateScore(mWinnerID, mLoserID, mScore):
    wGid = players[mWinnerID][1]
    lGid = players[mLoserID][1]
    groupScore[wGid] += mScore
    groupScore[lGid] -= mScore
 
 
 
 
def unionTeam(mPlayerA, mPlayerB):
    aGid = players[mPlayerA][1]
    bGid = players[mPlayerB][1]
    aSize = len(groupPlayers[aGid])
    bSize = len(groupPlayers[bGid])
 
    if aSize > bSize:
        bigGroup, smallGroup = groupPlayers[aGid], groupPlayers[bGid]
        bigGid, smallGid = aGid, bGid
    else:
        bigGroup, smallGroup = groupPlayers[bGid], groupPlayers[aGid]
        bigGid, smallGid  = bGid, aGid
 
    for pid in smallGroup:
        bigGroup.append(pid)
        players[pid][1] = bigGid
        players[pid][0] += groupScore[smallGid] - groupScore[bigGid]
 
    del groupPlayers[smallGid]
 
 
def getScore(mID):
    score, gid = players[mID][0], players[mID][1]
    score += groupScore[gid]
    return score