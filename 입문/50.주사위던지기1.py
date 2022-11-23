n, m = map(int, input().split())
arr, visited = [0]*n, [0, 0, 0, 0, 0, 0]
step = 0

def dice1(step):
  if step > n-1:
    for i in arr:
      print(i, end=' ')
    print()
    return 0
  for i in range(1, 7):
    arr[step] = i
    dice1(step+1)

def dice2(step):
  if step > n-1:
    for i in arr:
      print(i, end=' ')
    print()
    return 0
  for i in range(arr[step-1], 7):
    arr[step] = i
    dice2(step+1)

def dice3(step):
  if step > n-1:
    for i in arr:
      print(i, end=' ')
    print()
    return 0
  for i in range(1, 7):
    if visited[i-1]:
      continue
    visited[i-1] = 1
    arr[step] = i
    dice3(step+1)
    visited[i-1] = 0
    
if m == 1:
  dice1(0)
elif m == 2:
  for i in range(1, 7):
    arr[0] = i
    dice2(1)
else:
  dice3(0)