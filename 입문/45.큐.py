n = int(input())
stack = []

for _ in range(n):
    command = input().split()
    if command[0] == 'i':
        stack.append(int(command[1]))
    elif command[0] == 'c':
        print(len(stack))
    else:
        if len(stack) == 0:
            print("empty")
        else:
            print(stack.pop(0))
