string = input()
length = len(string)

koi, ioi = 0, 0

for i in range(length-2):
    if string[i] == 'K':
        if string[i+1] == 'O' and string[i+2] == 'I':
            koi += 1
    elif string[i] == 'I':
        if string[i+1] == 'O' and string[i+2] == 'I':
            ioi += 1

print(koi)
print(ioi)