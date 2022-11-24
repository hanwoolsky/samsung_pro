# 백트래킹 => 재귀호출, DFS
# 상태공간 트리

# 시간초과
n = int(input())
board = [[0]*n for _ in range(n)]

def check(r, c):
    for i in range(1, r+1):
        if board[r-i][c]:
            return 0
        if c-i >= 0 and board[r-i][c-i]:
            return 0
        if c+i < n and board[r-i][c+i]:
            return 0
    return 1
    

def DFS(cnt):
    global ans
    if cnt >= n:
        ans+=1
        return 0
    
    for i in range(n):
        if check(cnt, i):
            board[cnt][i] = 1
            DFS(cnt+1)
            board[cnt][i] = 0
    return 0

ans = 0
DFS(0)
print(ans)


# 그룹별 검사
n = int(input())
board = [[0]*n for _ in range(n)]
col = [0]*n
left = [0]*(2*n-1)
right = [0]*(2*n-1)

def DFS(cnt):
    global ans
    if cnt >= n:
        ans+=1
        return 0
    
    for i in range(n):
        if col[i] == 0 and left[cnt+i] == 0 and right[cnt-i+n-1] == 0:
            col[i], left[cnt+i], right[cnt-i+n-1] = 1, 1, 1
            DFS(cnt+1)
            col[i], left[cnt+i], right[cnt-i+n-1] = 0, 0, 0
    return 0

ans = 0
DFS(0)
print(ans)