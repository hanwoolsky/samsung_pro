# x, y의 범위가 2^31 - 1 이므로 시간초과
x, y = map(int, input().split())

ans = 1
for i in range(y):
    ans = x * ans % 20091024
print(ans)

# 재귀
def square(a, b):
    if b <= 0:
        return 1
    elif b % 2 == 1:
        return square(a, b-1) * a % 20091024
    else:
        tmp = square(a, b//2)
        return tmp * tmp % 20091024

x, y = map(int, input().split())
print(square(x, y))