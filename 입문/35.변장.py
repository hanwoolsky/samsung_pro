T = int(input())

while T > 0:
    N = int(input())
    dicts = dict()
    for _ in range(N):
        name, type = map(str, input().split())
        if type in dicts:
            dicts[type] += 1
        else:
            dicts[type] = 1
    ans = 1
    for key, value in dicts.items():
        ans *= (value+1)
    print(ans-1)
    T-=1