n, m = map(int, input().split())

for i in range(1, n+1):
    if i % 2 == 1:
        for j in range(i*m-(m-1), i*m-(m-1) + m):
            print(j, end=" ")
    else:
        for j in range(i*m, i*m-m, -1):
            print(j, end=" ")
    print()