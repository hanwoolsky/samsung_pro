def hanoi(num, s, e):
  if num < 1:
    return
  hanoi(num-1, s, 6-s-e)
  print(f"{num} : {s} -> {e}")
  hanoi(num-1, 6-s-e, e)

n = int(input())
hanoi(n, 1, 3)