D, K = map(int, input().split())

def fibo(n, a, b):
    arr = [0]*n

    arr[0] = a
    arr[1] = b

    for i in range(2, n):
        arr[i] = arr[i-1] + arr[i-2]
    
    return arr[n-1]

flag = False
iRange = K//D + 1
for i in range(1, iRange):
    for j in range(i+1, K-1):
        if fibo(D, i, j) == K:
            print(i)
            print(j)
            flag = True
            break
    if flag:
        break

# 거꾸로 탐색
arr = [0]*35

def check(d, n):
    arr[d-1] = n
    for i in range(d-2, 0, -1):
        arr[i] = arr[i+2] - arr[i+1]
        if arr[i] > arr[i+1]:
            return 0
    return 1

D, K = map(int, input().split())
arr[D] = K

for i in range(K//2, K+1):
    if check(D, i):
        break

print(arr[1])
print(arr[2])