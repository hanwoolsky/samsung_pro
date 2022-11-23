n = int(input())
m = int(input())
block = [[0]*n for _ in range(n)]
need = [0]*n
basic = [0]*n

def toy(num, cnt):
  if basic[num-1] == 0:
    need[num-1] += cnt
    return 0
  for i in range(n):
    if block[num-1][i]:
      toy(i+1, block[num-1][i]*cnt)
    
for _ in range(m):
  x, y, k = map(int, input().split())
  block[x-1][y-1] = k
  basic[x-1] = 1  

toy(n, 1)

for i in range(n):
  if basic[i] == 0:
    print(i+1, need[i])