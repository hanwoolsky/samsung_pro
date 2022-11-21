n = int(input())

ans, top = 0, 0
stack = [0]*80000

for _ in range(n):
    height = int(input())
    while  top > 0 and stack[top-1] <= height:
        top -= 1
    ans += top
    stack[top] = height
    top += 1

print(ans)