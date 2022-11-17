bin = int(input())
bin = str(bin)[::-1]

k = 1
sum = 0
for i in bin:
    sum += int(i)*k
    k *=2

print(sum)
