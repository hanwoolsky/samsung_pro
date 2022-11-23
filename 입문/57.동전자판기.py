# 그리디의 여집합을 이용

n = int(input())
coinCnt = list(map(int, input().split()))
coins = [500, 100, 50, 10, 5, 1]

total = 0
for i in range(6):
    total += coins[i]*coinCnt[i]

revTotal = total - n
revArr = [0]*6

for i in range(6):
    if revTotal//coins[i] < coinCnt[i]:
        revArr[i] = revTotal // coins[i]
    else:
        revArr[i] = coinCnt[i]
    revTotal -= revArr[i]*coins[i]

print(sum(coinCnt) - sum(revArr))
for i in range(6):
    print(coinCnt[i] - revArr[i], end=' ')