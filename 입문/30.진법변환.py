alpha = {10:'A', 11:'B', 12:'C', 13:'D', 14:'E', 15:'F', 16:'G', 17:'H', 18:'I', 19:'J',
        20:'K', 21:'L', 22:'M', 23:'N', 24:'O', 25:'P', 26:'Q', 27:'R', 28:'S', 29:'T',
        30:'U', 31:'V', 32:'W', 33:'X', 34:'Y', 35:'Z'}
betha = {'A':10, 'B':11, 'C':12, 'D':13, 'E':14, 'F':15, 'G':16, 'H':17, 'I':18, 'J':19,
        'K':20, 'L':21, 'M':22, 'N':23, 'O':24, 'P':25, 'Q':26, 'R':27, 'S':28, 'T':29,
        'U':30, 'V':31, 'W':32, 'X':33, 'Y':34, 'Z':35}

def aToDec(x, y):
    Astr = str(y)[::-1]

    k = 1
    sum = 0
    for i in Astr:
        if '0' <= i <= '9':
            sum += int(i)*k
        else:
            sum += betha[i]*k
        k *= x

    return sum

def decToB(x, y):
    ans = ""
    while x // y > 0:
        r = x % y
        x = x // y
        if r > 9:
            ans += alpha[r]
        else:
            ans += str(r)
    if x > 9:
        ans += alpha[x]
    else:
        ans += str(x)
    ans = ans[::-1]

    return ans

while True:
    arr = list(map(str, input().split()))
    if len(arr) == 1:
        break
    else:
        A, S, B = arr[0], arr[1], arr[2]
        
    print(decToB(aToDec(int(A), S), int(B)))