# 앞에서부터 더한 것 vs 나부터 시작하는 것을 비교

n = int(input())
arr = list(map(int, input().split()))
sums = [0]*n

sums[0] = arr[0]

for i in range(n-1):
    if sums[i] + arr[i+1] > arr[i+1]:
        sums[i+1] = sums[i] + arr[i+1]
    else:
        sums[i+1] = arr[i+1]

print(max(sums))