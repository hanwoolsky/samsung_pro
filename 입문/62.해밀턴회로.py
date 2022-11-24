n = int(input())
road = [list(map(int, input().split())) for _ in range(n)]
visited = [0]*n
ans = 1e9

def DFS(cnt, city, cost):
    global ans
    if cost >= ans:
        return
    if cnt >= n:
        ans = min(ans, cost + road[city][0])
        return 0

    for i in range(1, n):
        if visited[i] == 0:
            visited[i] = 1
            DFS(cnt+1, i, cost + road[city][i])
            visited[i] = 0


for i in range(n):
    for j in range(n):
        if road[i][j] == 0:
            road[i][j] = ans

DFS(1, 0, 0)
print(ans)