n, m = map(int, input().split())

if n < 1 or n > 100 or m not in [1, 2, 3]:
    print("INPUT ERROR!")
else:
    arr = [['']*n for _ in range(n)]
    if m == 1:
        for i in range(n):
            for j in range(i+1):
                print('*', end='')
            print()
    elif m == 2:
        for i in range(n):
            for j in range(i, n):
                print('*', end='')
            print()
    else:
        j = 1
        for i in range(n-1, -1, -1):
            print(' '*i+'*'*j+' '*i)
            j+=2
