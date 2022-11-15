n = int(input())
cnt = 1
arr = [[0]*n for _ in range(n)]

dx, dy = [1, -1, 0, 1], [0, 1, 1, -1]
dx1, dy1 = [1, 0, -1, 1], [-1, 1, 1, 0]
dx2, dy2 = [-1, 1, 1, 0], [1, 0, -1, 1]
dir, part = 0, n + int((n*n-n)/2)
part2 = n*n - part
x, y = 0, 0

while part:
    arr[x][y] = cnt
    cnt += 1
    x += dx[dir]
    y += dy[dir]

    if not 0 <= x + dx[dir] < n or not 0 <= y + dy[dir] < n or dir == 0 or dir == 2:
        dir = (dir + 1) % 4
        
    part -= 1

if n%2 == 0:
    x, y, dir = 1, n-1, 0
    dx, dy = dx1, dy1
else:
    x, y, dir = n-1, 1, 0
    dx, dy = dx2, dy2
while part2:
    arr[x][y] = cnt
    cnt += 1
    x += dx[dir]
    y += dy[dir]
    if not 0 <= x + dx[dir] < n or not 0 <= y + dy[dir] < n or dir == 1 or dir == 3:
        dir = (dir + 1) % 4
    part2 -= 1

for i in range(n):
    for j in range(n):
        print(arr[i][j], end = ' ')
    print()


# [simple way] / cpp
# while (num <= n*n){
#     arr[x][y] = num++;
#     if (x < n) x++;
#     else y++;

#     while (x > 1 && y < n) arr[x--][y++] = num ++;

#     arr[x][y] = num++;
#     if (y < n) y++;
#     else x++;

#     while (y > 1 && x < n) arr[x++][y--] = num++;
# }
