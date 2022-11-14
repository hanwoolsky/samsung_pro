n = int(input())

if n < 1 or n > 100 or n % 2 == 0:
    print("INPUT ERROR!")
else:
    arr = [['']*n for _ in range(n)]
    j = 1
    for i in range(int(n/2)):
        print(' '*i+'*'*j)
        j+=2
    for i in range(int(n/2), -1, -1):
        print(' '*i+'*'*j)
        j-=2