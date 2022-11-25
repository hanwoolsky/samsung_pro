import sys
sys.setrecursionlimit(10**5)

n, m = map(int, input().split())
board = []
dx, dy = [-1, 1, 0, 0], [0, 0, -1, 1]

for _ in range(n):
    board.append(list(map(int, input().split())))

def findAir(r, c):
    if 0 <= r < n and 0 <= c < m and board[r][c] == 0:
        board[r][c] = 2
        for i in range(4):
            findAir(r+dx[i], c+dy[i])
    return 0

def melt():
    cheese = 0
    for i in range(n):
        for j in range(m):
            if board[i][j] == 1:
                for k in range(4):
                    if board[i+dx[k]][j+dy[k]] == 2:
                        board[i][j] = 0 # 다 0됨
                        cheese += 1
                        break

    return cheese

def newAir():
    for i in range(n):
        for j in range(m):
            if board[i][j] == 2:
                board[i][j] = 0
    return 0

tmp, left, cnt = 1, 0, 0

while tmp:
    findAir(0, 0) # DFS
    tmp = melt()
    if tmp == 0:
        break
    newAir()
    cnt += 1
    left = tmp
print(cnt)
print(left)