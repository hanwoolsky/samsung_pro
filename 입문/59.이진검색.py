n = int(input())
arr = list(map(int, input().split()))
m = int(input())
targetArr = list(map(int, input().split()))

def bs(target, s, e):
    if s > e:
        return -1

    mid = (s+e)//2
    if arr[mid] == target:
        return mid
    elif arr[mid] > target:
        return bs(target, s, mid-1)
    else:
        return bs(target, mid+1, e)

for i in range(m):
    ans = bs(targetArr[i], 0, n-1)
    print(ans, end=' ')