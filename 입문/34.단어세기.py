# 딕셔너리 정렬
while True:
    string = input()
    dicts = dict()
    if string == "END":
        break
    arr = list(string.split())
    for i in arr:
        if i in dicts:
            dicts[i] += 1
        else:
            dicts[i] = 1
    for key, value in sorted(dicts.items()):
        print(key, ":", value)