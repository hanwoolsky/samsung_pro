n = int(input())
conf = []

for _ in range(n):
  idx, s, e = map(int, input().split())
  conf.append((idx, s, e))

conf.sort(key=lambda x : x[2])

st, en = conf[0][1], conf[0][2]
ans = [conf[0][0]]
for i in range(1, n):
  if conf[i][1] >= en:
    en = conf[i][2]
    ans.append(conf[i][0])

print(len(ans))
for i in ans:
  print(i, end=' ')