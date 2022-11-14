alpha = {0:'A', 1:'B', 2:'C', 3:'D', 4:'E', 5:'F', 6:'G', 7:'H', 8:'I', 9:'J',
        10:'K', 11:'L', 12:'M', 13:'N', 14:'O', 15:'P', 16:'Q', 17:'R', 18:'S',
        19:'T', 20:'U', 21:'V', 22:'W', 23:'X', 24:'Y', 25:'Z'}

n = int(input())
arr = [[1]*n for _ in range(n)]
cnt = 0
for i in range(n-1, -1, -1):
    for j in range(n-1, -1, -1):
        arr[j][i] = cnt
        cnt = (cnt+1)%26

for i in range(n):
    for j in range(n):
        print(alpha[arr[i][j]], end=" ")
    print()