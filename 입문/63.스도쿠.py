board = [list(map(int, input().split())) for _ in range(9)]
row = [[0]*9 for _ in range(9)]
col = [[0]*9 for _ in range(9)]
grp = [[0]*9 for _ in range(9)]

def sudoku(r, c):
    if c > 8:
        r += 1
        c = 0
    if r > 8:
        return 1
    if board[r][c]:
        return sudoku(r, c+1)

    g = r//3*3+c//3
    for i in range(9):
        if row[r][i] == 0 and col[c][i] == 0 and grp[g][i] == 0:
            row[r][i], col[c][i], grp[g][i] = 1, 1, 1
            board[r][c] = i+1
            if sudoku(r, c+1):
                return 1
            board[r][c] = 0
            row[r][i], col[c][i], grp[g][i] = 0, 0, 0
    return 0

for i in range(9):
    for j in range(9):
        if board[i][j]:
            k = board[i][j]
            row[i][k-1] , col[j][k-1], grp[i//3*3+j//3][k-1] = 1, 1, 1

sudoku(0, 0)
for i in range(9):
    for j in range(9):
        print(board[i][j], end=' ')
    print()