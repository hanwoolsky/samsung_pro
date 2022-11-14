n = int(input())

for i in range(1, n+1):
    for j in range(i, i + n*(n-1)+1, n):
        print(j, end=" ")
    print()