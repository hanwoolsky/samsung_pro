n = int(input())
arr = [0]*n
for i in range(n):
    arr[i] = int(input())

def isPrime(x):
    if x < 2:
        return 0
    sqrt = int(x ** 0.5)
    count = 0

    for i in range(2, sqrt+1):
        if x % i == 0:
            count += 1
    if count == 0:
        return 1
    else:
        return 0

for i in arr:
    flag = False
    for j in range(i+1):
        if isPrime(i-j):
            flag = True
            print(i-j, end=' ')
        if isPrime(i+j):
            flag = True
            if j != 0:
                print(i+j, end=' ')
        if flag:
            break
    print()