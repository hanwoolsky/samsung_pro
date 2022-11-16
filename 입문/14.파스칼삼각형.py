n, m = map(int, input().split())
arr = [[0]*n for _ in range(n)]

def fact(n):
    ans = 1
    for i in range(1, n+1):
        ans *= i
    return ans

def comp(x, y):
    if x == 0 or y == 0:
        return 1
    else:
        return fact(x) // (fact(y)*fact(x-y))

for i in range(n):
    for j in range(i+1):
        if m == 3:
            arr[n-j-1][n-i-1] = comp(i, j)
        else:
            arr[i][j] = comp(i, j)

if m == 1 or m == 3:
    for i in range(n):
        for j in range(i+1):
            print(arr[i][j], end=' ')
        print()

else:
    k = 0
    for i in range(n-1, -1, -1):
        print(' '*k, end='')
        for j in range(n-k):
            print(arr[i][j], end=' ')
        print(' '*k)
        k+=1
