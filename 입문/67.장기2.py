from collections import deque

n, m = map(int, input().split())
r, c, s, k = map(int, input().split())
board = [[0]*m for _ in range(n)]
dx, dy = [-2, -2, -1, 1, 2, 2, 1, -1], [-1, 1, 2, 2, 1, -1, -2, -2]

queue = deque()
queue.append((r-1, c-1))
board[r-1][c-1] = 1

while queue:
  x, y = queue.popleft()
  if x == s-1 and y == k-1:
    break
  for i in range(8):
    nx = x + dx[i]
    ny = y + dy[i]
    if 0<=nx<n and 0<=ny<m and board[nx][ny] == 0:
      board[nx][ny] = board[x][y] + 1
      queue.append((nx, ny))

print(board[s-1][k-1] - 1)