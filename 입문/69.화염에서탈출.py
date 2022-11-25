from collections import deque

n, m = map(int, input().split())
board = [[0]*m for _ in range(n)]
dx, dy = [-1, 0, 1, 0], [0, 1, 0, -1]
ds, de, ss, se = -1, -1, -1, -1
queue = deque()

def push(nx, ny, t, cnt):
    if nx < 0 or nx >= n or ny < 0 or ny >= m or board[nx][ny]:
        return 0
    if nx == ds and ny == de:
        return t

    board[nx][ny] = 1
    queue.append((nx, ny, t, cnt))

    return 0

def BFS():
    push(ss, se, 1, 0)
    while queue:
        x, y, type, cnt = queue.popleft()
        for i in range(4):
            if push(x + dx[i], y + dy[i], type, cnt+1):
                return cnt + 1
    return -1

for i in range(n):
    map = input()
    for j in range(m):
        if map[j] == 'D':
            ds, de = i, j
        elif map[j] == 'S':
            ss, se = i, j
        elif map[j] == '*':
            push(i, j, 0, 0)
        elif map[j] == 'X':
            board[i][j] = 1 # 바위
        else:
            board[i][j] = 0

ans = BFS()
if ans == -1:
    print("impossible")
else:
    print(ans)