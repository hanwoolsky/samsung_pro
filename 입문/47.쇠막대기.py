par = input()
length = len(par)

stack = []
stick = 0

for i in range(length):
  if par[i] == "(":
    stack.append("(")
  else:
    if par[i-1] == "(":
      stack.pop()
      stick += len(stack)
    else:
      stack.pop()
      stick += 1

print(stick)