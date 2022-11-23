n, m = map(int, input().split())
arr = [0]*n

def dice(step, sums):
  if step == n - 1:
      if 0 < sums < 7:
        arr[step] = sums
        for i in arr:
          print(i, end=' ')
        print()
      return
  for i in range(1, 7):
    if sums >= i:
        arr[step] = i
        sums -= i
        dice(step+1, sums)
        sums += i
      
dice(0, m)