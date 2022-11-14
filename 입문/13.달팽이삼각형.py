n = int(input())
cnt = 0
arr = [['']*n for _ in range(n)]

dx, dy = [1, 0, -1], [1, -1, 0]
dir, total = 0, n*(n+1)//2
dirCout = n
x, y = 0, 0

while total:
    arr[x][y] = cnt
    cnt = (cnt + 1) % 10
    if not 0 <= x + dx[dir] < n or not 0 <= y + dy[dir] < n or arr[x + dx[dir]][y + dy[dir]] != '':
        dir = (dir + 1) % 3
    x += dx[dir]
    y += dy[dir]
    total -= 1

for i in range(n):
    for j in range(n):
        if arr[i][j] != '':
            print(arr[i][j], end = ' ')
    print()
