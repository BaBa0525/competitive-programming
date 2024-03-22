n = int(input())

e: float = 0
base = 1
for i in range(n + 1):
    if i == 0:
        e += 1
        continue

    base *= i
    e += 1 / base


print(e)
