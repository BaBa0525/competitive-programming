import math

a, b = map(int, input().split())
ans: list[tuple[int, int]] = []


def count_digit(x: int, times: list[int] | None = None):
    if times is None:
        times = [0] * 10

    while x != 0:
        d, m = divmod(x, 10)
        times[m] += 1
        x = d

    return times


for x in range(a, int(math.sqrt(b)) + 1):
    for y in range(x, b + 1):
        if x * y > b:
            break

        xy = x * y
        times1 = count_digit(y, count_digit(x))
        times2 = count_digit(xy)

        if times1 == times2:
            ans.append((x, y))


print(f"{len(ans)} digit-preserving pair(s)")

for x, y in ans:
    print(f"{x = }, {y = }, xy = {x*y}")
