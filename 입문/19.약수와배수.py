n = int(input())
arr = list(map(int, input().split()))
m = int(input())

yakSum = 0
beSum = 0
for i in arr:
    if m % i == 0:
        yakSum += i
    if i % m == 0:
        beSum += i

print(yakSum)
print(beSum)