arr = list(map(int, input().split()))

def isPrime(x):
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
    if i == 1:
        print("number one")
    elif isPrime(i):
        print("prime number")
    else:
        print("composite number")