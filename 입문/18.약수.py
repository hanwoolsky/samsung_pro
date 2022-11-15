# [시간초과]
# n = int(input())

# for i in range(1, n+1):
#     if n % i == 0:
#         print(i, end=' ')

# [제곱근]
n = int(input())
sq = int(n ** (0.5))
arr = [n]*10000
cnt = 0

for i in range(1, sq+1):
    if n % i == 0:
        arr[cnt] = i
        cnt += 1
        if n / i > i:
            arr[cnt] = n // i
            cnt += 1
arr.sort()
for i in arr:
    print(i, end=' ')
    if i == n:
        break