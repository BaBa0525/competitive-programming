n = int(input())

for _ in range(n):
    params = list(map(int, input().split()))
    a, b = params[0:-2:2], params[1:-2:2]
    c, d = params[-2], params[-1]

    line = list(map(int, input().split()))
    x, y = line[0::2], line[1::2]

    results: list[list[int | None]] = [[None for _ in range(100)] for _ in range(100)]

    def f(x: int, y: int) -> int:
        if x <= 0 or y <= 0:
            return d

        if results[x][y] is not None:
            return results[x][y]  # type: ignore

        ans = c
        for ai, bi in zip(a, b):
            ans += f(x - ai, y - bi)

        results[x][y] = ans
        return ans

    for xi, yi in zip(x, y):
        print(f(xi, yi))

    print()
