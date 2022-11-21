n = int(input())
arr = [[0, 0, 0, 0, 0] for _ in range(n)]

for i in range(n):
    pred, strike, ball = map(int, input().split())
    for j in range(3):
        arr[i][j] = int(str(pred)[j])
    arr[i][3], arr[i][4] = strike, ball

def check(N):
    for i in range(n):
        s, b, cnt = 0, 0, 0
        for j in range(3):
            if int(str(N)[j]) == arr[i][j]:
                s+=1
        if s != arr[i][3]:
            return 0
        for j in range(3):
            if int(str(N)[j]) != arr[i][j] and int(str(N)[j]) in arr[i][0:3]:
                b+=1
        if b != arr[i][4]:
            return 0
        cnt+=1
        
    return cnt

ans = 0
for i in range(123, 988):
    a, b, c = str(i)[0], str(i)[1], str(i)[2]
    if a != b and b != c and a != c and a != '0' and b != '0' and c != '0':
        ans += check(i)

print(ans)