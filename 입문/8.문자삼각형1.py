alpha = {-1: ' ', 0:'A', 1:'B', 2:'C', 3:'D', 4:'E', 5:'F', 6:'G', 7:'H', 8:'I', 9:'J',
        10:'K', 11:'L', 12:'M', 13:'N', 14:'O', 15:'P', 16:'Q', 17:'R', 18:'S',
        19:'T', 20:'U', 21:'V', 22:'W', 23:'X', 24:'Y', 25:'Z'}

n = int(input())
arr = [[-1]*n for _ in range(n)]
cnt, k = 0, n

for i in range(n):
    for j in range(i, n):
        arr[j][k-j-1] = cnt
        cnt = (cnt + 1) % 26
    k+=1

for i in range(n):
    for j in range(n):
        print(alpha[arr[i][j]], end=' ')
    print()