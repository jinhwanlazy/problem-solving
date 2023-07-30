from collections import defaultdict
N = int(input())
xs = list(map(int, input().split()))
res = {xs[0]: 1}
for i in range(1, N - 1):
    nxt = defaultdict(int)
    x = xs[i]
    for i, c in res.items():
        if 0 <= i + x <= 20:
            nxt[i + x] += c
        if 0 <= i - x <= 20:
            nxt[i - x] += c
    res = nxt
print(res[xs[-1]])
