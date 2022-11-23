number = list(map(int, input().split()))
num = number[0]
number = number[1:num+1]
case = [0]*num

def lotto(start, cnt):
  if cnt == 6:
    for i in range(num):
      if case[i]:
        print(number[i], end=' ')
    print()
  for i in range(start, num):
    case[i] = 1
    lotto(i+1, cnt+1)
    case[i] = 0

lotto(0, 0)