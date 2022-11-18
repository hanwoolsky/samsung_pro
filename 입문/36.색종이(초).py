n = int(input())
paper = [[0]*100 for _ in range(100)]

for _ in range(n):
    x, y = map(int, input().split())

    for i in range(x, x+10):
        for j in range(y, y+10):
            paper[i][j] = 1

sums = 0
for i in range(100):
    sums += sum(paper[i])

print(sums)