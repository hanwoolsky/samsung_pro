n = int(input())
m = int(input())

def isPrime(x):
    sqrt = int(x ** 0.5)
    count = 0
    if x == 1:
        return 0

    for i in range(2, sqrt+1):
        if x % i == 0:
            count += 1
    if count == 0:
        return 1
    else:
        return 0

sum, min = 0, 1e9
for i in range(n, m+1):
    if isPrime(i):
        sum += i
        if min > i:
            min = i

if sum == 0:
    print(-1)
else:
    print(sum)
    print(min)