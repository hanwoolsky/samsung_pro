n, m = map(int, input().split())
ans = ""
alpha = {10: 'A', 11: 'B', 12: 'C', 13: 'D', 14: 'E', 15: 'F'}

if m == 2:
    while n // 2 > 0:
        r = n % 2
        n = n // 2
        ans += str(r)
    ans += str(n)
    ans = ans[::-1]
elif m == 8:
    while n // 8 > 0:
        r = n % 8
        n = n // 8
        ans += str(r)
    ans += str(n)
    ans = ans[::-1]
else:
    while n // 16 > 0:
        r = n % 16
        n = n // 16
        if r > 9:
            ans += alpha[r]
        else:
            ans += str(r)
    if n > 9:
        ans += alpha[n]
    else:
        ans += str(n)
    ans = ans[::-1]

print(ans)