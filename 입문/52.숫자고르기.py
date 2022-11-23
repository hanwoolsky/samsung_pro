n = int(input())
arr = [0]*n
select = [0]*n
visited = [0]*n
cnt = 0

def sel(s, now):
  global cnt
  if s == now:
    cnt += 1
    return 1
  elif visited[now-1]:
    return 0
  visited[now-1] = 1
  return sel(s, arr[now-1])

for i in range(n):
  arr[i] = int(input())

for i in range(n):
  for j in range(n):
    visited[j] = 0
  select[i] = sel(i+1, arr[i])

print(cnt)
for i in range(n):
  if select[i]:
    print(i+1)