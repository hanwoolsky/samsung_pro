board = [list(map(int, input().split())) for _ in range(5)]
called = [list(map(int, input().split())) for _ in range(5)]
coord = [(0,0)]*25

def bingo():
    cnt = 0
    for i in range(5):
        for j in range(5):
            if board[i][j]:
                break
        if j == 4 and not board[i][j]:
            cnt+=1

        for j in range(5):
            if board[j][i]:
                break
        if j == 4 and not board[j][i]:
            cnt+=1

    for i in range(5):
        if board[i][i]:
            break
    if i == 4 and not board[i][i]:
        cnt+=1
    for i in range(5):
        if board[i][4-i]:
            break
    if i == 4 and not board[i][4-i]:
        cnt+=1
    
    if cnt > 2:
        return 1
    return 0

for i in range(5):
    for j in range(5):
        coord[board[i][j]-1] = (i, j)

ans, flag = 0, 0

for i in range(5):
    for j in range(5):
        ans += 1
        x, y = coord[called[i][j]-1]
        board[x][y] = 0
        if bingo():
            print(ans)
            flag = 1
            break
    if flag:
        break