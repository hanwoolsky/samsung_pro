alpha = {-1: ' ', 0:'A', 1:'B', 2:'C', 3:'D', 4:'E', 5:'F', 6:'G', 7:'H', 8:'I', 9:'J',
        10:'K', 11:'L', 12:'M', 13:'N', 14:'O', 15:'P', 16:'Q', 17:'R', 18:'S',
        19:'T', 20:'U', 21:'V', 22:'W', 23:'X', 24:'Y', 25:'Z'}

n = int(input())
size = 2*n-1
cnt = 0
arr = [[-1]*size for _ in range(size)]
x, y, move = 0, n-1, n-1

for i in range(move, 0, -1):
    for j in range(i):
        arr[x][y] = cnt
        x += 1
        y -= 1
        cnt = (cnt + 1) % 26
    for j in range(i):
        arr[x][y] = cnt
        x += 1
        y += 1
        cnt = (cnt + 1) % 26
    for j in range(i):
        arr[x][y] = cnt
        x -= 1
        y += 1
        cnt = (cnt + 1) % 26
    for j in range(i):
        arr[x][y] = cnt
        x -= 1
        y -= 1
        cnt = (cnt + 1) % 26
    x += 1
arr[x][y] = cnt

for i in range(size):
    for j in range(size):
        print(alpha[arr[i][j]], end = ' ')
    print()
