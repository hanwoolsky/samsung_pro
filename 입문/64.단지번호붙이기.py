n = int(input())
village = [[0]*n for _ in range(n)]
danji = []

def BFS(x, y):
    k = 1
    if x < 0 or y < 0 or x > n-1 or y > n-1:
        return 0
    
    if village[x][y] == 0:
        return 0

    village[x][y] = 0

    k += BFS(x, y+1)
    k += BFS(x+1, y)
    k += BFS(x, y-1)
    k += BFS(x-1, y)
    return k

for i in range(n):
    vil = input()
    for j in range(n):
        village[i][j] = int(vil[j])

ans = 0
for i in range(n):
    for j in range(n):
        if village[i][j]:
            k = BFS(i, j)
            danji.append(k)


print(len(danji))
danji.sort()
for i in danji:
    print(i)