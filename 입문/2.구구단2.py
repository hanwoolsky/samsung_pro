while True:
    s, e = map(int, input().split())
    if 1 < s < 10 and 1 < e < 10:
        break
    else:
        print("INPUT ERROR!")

if s < e:
    for j in range(s, e+1):
        for i in range(1, 10):
            print(f"{j} * {i} = {j*i:2}", end="   ")
            if i % 3 == 0:
                print()
        print()    
else:
    for j in range(s, e-1, -1):
        for i in range(1, 10):
            print(f"{j} * {i} = {j*i:2}", end="   ")
            if i % 3 == 0:
                print()
        print()