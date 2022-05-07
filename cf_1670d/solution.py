import sys
input = sys.stdin.readline

from bisect import bisect_left


def f(a, b, c):
    a, b, c = sorted((a, b, c))
    return b, a+1, c, 2 * (b + c)

a, b, c = 0, 0, 0
dp = []
while not dp or dp[-1] < 1e9:
    a, b, c, v = f(a, b, c)
    if not dp:
        dp.append(v)
    else:
        dp.append(dp[-1] + v)

for _ in range(int(input())):
    n = int(input())
    ans = bisect_left(dp, n)
    print(ans + 1)


