while True:
    s, e = map(int, input().split())
    if 1 < s < 10 and 1 < e < 10:
        break
    else:
        print("INPUT ERROR!")

for i in range(1, 10):
    if s < e:
        for j in range(s, e+1):
            print(f"{j} * {i} = {j*i:2}", end="   ")
    else:
        for j in range(s, e-1, -1):
            print(f"{j} * {i} = {j*i:2}", end="   ")
    print()


# 자릿수를 맞추고 싶을때 :n 을 붙이면 n칸을 차지하게 맞춰진다.