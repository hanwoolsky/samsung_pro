# 유클리드 호제법 : A, B의 최대공약수는 A를 B로 나눈 나머지와 B의 최대공약수와 같다.

def GCD(A, B):
    while B!=0:
        r = A % B
        A = B
        B = r
    return A

def LCM(A, B):
    return A * B // GCD(A, B)

A, B = map(int, input().split())
print(GCD(A, B))
print(LCM(A, B))