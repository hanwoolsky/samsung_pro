# 에라토스테네스의 체

n, m = map(int, input().split())
arr = [1]*2000000
arr[0] = 0

def eratos(x):
    sqrt = int(x**0.5)
    for i in range(2, sqrt+1):
        if arr[i-1] == 1:
            for j in range(i*i, x+1, i):
                arr[j-1] = 0

eratos(m)
print(sum(arr[n-1:m]))