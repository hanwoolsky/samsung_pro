# 분할정복
N = int(input())
board = [list(map(int, input().split())) for _ in range(N)]
color = [0]*2

def colUni(r, c, len):
    for i in range(len):
        for j in range(len):
            if board[r+i][c+j] != board[r][c]:
                return 0
    return 1

def divCon(x, y, n):
    if colUni(x, y, n):
        color[board[x][y]] += 1
        return 0
    else:
        m = int(n//2)
        divCon(x, y, m)
        divCon(x + m, y, m)
        divCon(x, y + m, m)
        divCon(x + m, y + m, m)

divCon(0, 0, N)

print(color[0])
print(color[1])