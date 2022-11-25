n, m = map(int, input().split())
r, c, s, k = map(int, input().split())
board = [[100]*m for _ in range(n)]
dx, dy = [-2, -2, -1, 1, 2, 2, 1, -1], [-1, 1, 2, 2, 1, -1, -2, -2]

def DFS(r, c, cnt):
    if r < 1 or r > n or c < 1 or c > m:
        return
    if board[r-1][c-1] <= cnt or board[s-1][k-1] <= cnt:
        return
    board[r-1][c-1] = cnt
    for i in range(8):
        DFS(r+dx[i], c+dy[i], cnt+1)
        
DFS(r, c, 0)
print(board[s-1][k-1])