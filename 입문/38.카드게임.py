color = [""]*5
number = [0]*5
count = [0]*9

for i in range(5):
    c, n = map(str, input().split())
    color[i] = c
    number[i] = int(n)

setColor = set(color)
sortNumber = sorted(number)
score = 0

def isContinuous(arr):
    for i in range(4):
        if arr[i+1] - arr[i] != 1:
            return False
    return True

if len(set(color)) == 1 and isContinuous(sortNumber):
    score = 900 + sortNumber[-1]

elif sortNumber[0] == sortNumber[3] or sortNumber[1] == sortNumber[4]:
    score = 800 + sortNumber[1]

elif sortNumber[0] == sortNumber[2] and sortNumber[3] == sortNumber[4]:
    score = 700 + sortNumber[2]*10 + sortNumber[3]
elif sortNumber[0] == sortNumber[1] and sortNumber[2] == sortNumber[4]:
    score = 700 + sortNumber[2]*10 + sortNumber[0]

elif len(set(color)) == 1:
    score = 600 + sortNumber[-1]

elif isContinuous(sortNumber):
    score = 500 + sortNumber[-1]

elif sortNumber[0] == sortNumber[1] and sortNumber[1] == sortNumber[2]:
    score = 400 + sortNumber[0]
elif sortNumber[1] == sortNumber[2] and sortNumber[2] == sortNumber[3]:
    score = 400 + sortNumber[1]
elif sortNumber[2] == sortNumber[3] and sortNumber[3] == sortNumber[4]:
    score = 400 + sortNumber[2]

elif sortNumber[0] == sortNumber[1] and sortNumber[2] == sortNumber[3]:
    score = 300 + max(sortNumber[0], sortNumber[2])*10 + min(sortNumber[0], sortNumber[2])
elif sortNumber[0] == sortNumber[1] and sortNumber[3] == sortNumber[4]:
    score = 300 + max(sortNumber[0], sortNumber[3])*10 + min(sortNumber[0], sortNumber[3])
elif sortNumber[1] == sortNumber[2] and sortNumber[3] == sortNumber[4]:
    score = 300 + max(sortNumber[1], sortNumber[3])*10 + min(sortNumber[1], sortNumber[3])

elif sortNumber[0] == sortNumber[1]:
    score = 200 + sortNumber[0]
elif sortNumber[1] == sortNumber[2]:
    score = 200 + sortNumber[1]
elif sortNumber[2] == sortNumber[3]:
    score = 200 + sortNumber[2]
elif sortNumber[3] == sortNumber[4]:
    score = 200 + sortNumber[3]

else:
    score = 100 + sortNumber[-1]

print(score)
