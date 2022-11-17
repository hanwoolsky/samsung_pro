# 'a' = 97, 'A' = 65
bok = input()
msg = input()

alpha = dict()
alpha[' '] = ' '
lowerNum = 97
upperNum = 65

for i in bok:
    alpha[chr(lowerNum)] = i
    alpha[chr(upperNum)] = chr(ord(i) - 32)
    lowerNum += 1
    upperNum += 1

ans = ""
for i in msg:
    ans += alpha[i]

print(ans)