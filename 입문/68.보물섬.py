from collections import deque

n, m = map(int, input().split())
treasure = [[0]*m for _ in range(n)]
dx, dy = [-1, 0, 1, 0], [0, 1, 0, -1]

def BFS(r, c):
    cnt = 0
    visit = [[0]*m for _ in range(n)]
    if treasure[r][c] == 0 or visit[r][c] == 1:
        return
    visit[r][c] = 1
    queue.append((r, c, 0))
    while queue:
        x, y, cnt = queue.popleft()
        for i in range(4):
            nx = x + dx[i]
            ny = y + dy[i]
            if 0<=nx<n and 0<=ny<m:
                if treasure[nx][ny] == 1 and visit[nx][ny] == 0:
                    visit[nx][ny] = 1
                    queue.append((nx, ny, cnt+1))
    return cnt

for i in range(n):
    map = input()
    for j in range(m):
        if map[j] == 'W':
            treasure[i][j] = 0
        else:
            treasure[i][j] = 1

queue = deque()
ans = 0

for i in range(n):
    for j in range(m):
        if treasure[i][j] == 1:
            far = BFS(i, j)
            if far > ans:
                ans = far
print(ans)