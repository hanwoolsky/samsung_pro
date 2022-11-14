n = int(input())
cnt = 1
arr = [[0]*n for _ in range(n)]

dx, dy = [0, 1, 0, -1], [1, 0, -1, 0]
dir, total = 0, n*n
dirCout = n
x, y = 0, 0

while total:
    arr[x][y] = cnt
    cnt += 1
    if not 0 <= x + dx[dir] < n or not 0 <= y + dy[dir] < n or arr[x + dx[dir]][y + dy[dir]] != 0:
        dir = (dir + 1) % 4
    x += dx[dir]
    y += dy[dir]
    total -= 1

for i in range(n):
    for j in range(n):
        print(arr[i][j], end = ' ')
    print()
