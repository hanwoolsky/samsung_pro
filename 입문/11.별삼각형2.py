n, m = map(int, input().split())

if n < 1 or n > 100 or n % 2 == 0 or m not in [1, 2, 3, 4]:
    print("INPUT ERROR!")
else:
    arr = [['']*n for _ in range(n)]
    if m == 1:
        k = 1
        flag = True
        for i in range(n):
            print('*'*k)
            if k < n/2 and flag:
                k+=1
            else:
                flag = False
                k-=1
    elif m == 2:
        k = 1
        flag = True
        for i in range(n):
            print(' '*(int(n/2)+1-k)+'*'*k)
            if k < n/2 and flag:
                k+=1
            else:
                flag = False
                k-=1
    elif m == 3:
        j = n
        for i in range(int(n/2)):
            print(' '*i+'*'*j+' '*i)
            j-=2
        for i in range(int(n/2), -1 , -1):
            print(' '*i+'*'*j+' '*i)
            j+=2
    else:
        j = int(n/2) + 1
        for i in range(int(n/2)):
            print(' '*i+'*'*j)
            j-=1
        for i in range(int(n/2), -1 , -1):
            print(' '*int(n/2)+'*'*j)
            j+=1
