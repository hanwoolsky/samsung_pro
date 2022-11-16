while True:
    n = int(input())
    n = str(n)

    if n == '0':
        break

    sum = 0
    for i in n:
        sum += int(i)

    reverse = n[::-1]
    j = 0
    for i in reverse:
        if i == '0':
            j += 1
        else:
            break
    print(reverse[j:], sum)