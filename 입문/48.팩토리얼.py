n = int(input())
ans = 1
for i in range(n, 0, -1):
    ans *= i
    if i == 1:
        print("1! = 1")
    else:
        print(f"{i}! = {i} * {i-1}!")
print(ans)