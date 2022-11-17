sets = set()
ans = list()

while True:
    string = input()
    if string == "END":
        break
    arr = list(string.split())
    for i in arr:
        sets.add(i)
        if len(sets) != len(ans):
            ans.append(i)
    for i in ans:
        print(i, end=' ')
    print()
    