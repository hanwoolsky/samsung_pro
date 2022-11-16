def GCD(A, B):
    while B!=0:
        r = A % B
        A = B
        B = r
    return A

def LCM(A, B):
    return A * B // GCD(A, B)

n = int(input())
arr = list(map(int, input().split()))
gcd, lcm = arr[0], arr[0]

for i in range(1, n):
    gcd = GCD(gcd, arr[i])
    lcm = lcm * arr[i] // GCD(lcm, arr[i])

print(gcd, lcm)