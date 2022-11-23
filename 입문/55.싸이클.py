n, p = map(int, input().split())
dictionary = dict()

cnt, num = 1, n
dictionary[n] = cnt

while True:
  cnt+=1
  num = num * n % p
  if num in dictionary:
    break
  dictionary[num] = cnt

print(cnt - dictionary[num])