from collections import deque

n, m = map(int, input().split())
board = [list(map(int, input().split())) for _ in range(n)]

dx, dy = [0, 0, 1, -1], [1, -1, 0, 0]
queue = deque()
check = [[[0]*4 for _ in range(m)] for _ in range(n)]


ss, se, sdir = map(int, input().split())
ds, de, ddir = map(int, input().split())

def push(nx, ny, d, cnt):
    if check[nx][ny][d]:
       return 0
    check[nx][ny][d] = 1
    queue.append((nx, ny, d, cnt))

    if nx == ds-1 and ny == de-1 and d == ddir-1:
        return 1
    return 0


def BFS():
    push(ss-1, se-1, sdir-1, 0)
    while queue:
        x, y, dir, cnt = queue.popleft()
        if dir < 2:
            if(push(x, y, 2, cnt+1)):
                return cnt + 1
            if(push(x, y, 3, cnt+1)):
                return cnt + 1
        else:
            if(push(x, y, 0, cnt+1)):
                return cnt + 1
            if(push(x, y, 1, cnt+1)):
                return cnt + 1
        
        for i in range(1, 4):
            x += dx[dir]
            y += dy[dir]
            if x < 0 or x >= n or y < 0 or y >= m or board[x][y]:
                break
            if(push(x, y, dir, cnt+1)):
                    return cnt + 1
    return 0

ans = BFS()
print(ans)