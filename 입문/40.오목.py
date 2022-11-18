board = [list(map(int, input().split())) for _ in range(19)]

dx, dy = [-1, 0, 1, 1], [1, 1, 1, 0]

def checkWin(x, y, c):
    for i in range(4):
        count, a, b = 0, x, y
        for _ in range(4):
            nx = a + dx[i]
            ny = b + dy[i]
            if 0 <= nx < 19 and 0 <= ny < 19 and board[nx][ny] == c:
                count+=1
                a, b = nx, ny
        if count == 4:
            if 0 <= x - dx[i] < 19 and 0 <= y - dy[i] < 19 and board[x - dx[i]][y - dy[i]] == c:
                return 0
            if 0 <= a + dx[i] < 19 and 0 <= b + dy[i] < 19 and board[a + dx[i]][b + dy[i]] != c:
                return 1
            elif  not 0 <= a + dx[i] < 19 or not 0 <= b + dy[i] < 19:
                return 1
    return 0

flag = False
for i in range(19):
    for j in range(19):
        if board[i][j] == 1:
            if checkWin(i, j, 1):
                print(1)
                print(i+1, j+1)
                flag = True
                break
        elif board[i][j] == 2:
            if checkWin(i, j, 2):
                print(2)
                print(i+1, j+1)
                flag = True
                break
    if flag:
        break

if flag == False:
    print(0)