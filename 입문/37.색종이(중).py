n = int(input())
paper = [[0]*102 for _ in range(102)]

for _ in range(n):
    x, y = map(int, input().split())

    for i in range(x+1, x+11):
        for j in range(y+1, y+11):
            paper[i][j] = 1

ans = 0
for i in range(101):
    for j in range(101):
        if paper[i][j] == 1:
            ans = ans + 4 - paper[i+1][j] - paper[i-1][j] - paper[i][j+1] - paper[i][j-1]

print(ans)