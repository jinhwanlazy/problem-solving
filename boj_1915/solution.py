n, m = map(int, input().split())

w = [list(map(int, input().strip())) for _ in range(n)]

dp_v = [[0] * m for _ in range(n)]
dp_h = [[0] * m for _ in range(n)]
dp = [[0] * m for _ in range(n)]

for r in range(n):
    for c in range(m):
        if r == 0:
            dp_v[r][c] = w[r][c]
        else:
            dp_v[r][c] = 0 if w[r][c] == 0 else dp_v[r-1][c] + 1

for c in range(m):
    for r in range(n):
        if c == 0:
            dp_h[r][c] = w[r][c]
        else:
            dp_h[r][c] = 0 if w[r][c] == 0 else dp_h[r][c-1] + 1

ans = 0
for r in range(n):
    for c in range(m):
        if r == 0 or c == 0:
            dp[r][c] = dp_v[r][c] & dp_h[r][c]
        elif w[r][c] == 0:
            dp[r][c] = 0
        else:
            h = dp_h[r][c]
            v = dp_v[r][c]
            prv = dp[r-1][c-1]
            if v > prv and h > prv:
                dp[r][c] = prv + 1
            else:
                dp[r][c] = min(h, v, prv)
        ans = max(ans, dp[r][c])

# from pprint import pprint
# pprint(dp_v)
# pprint(dp_h)
# pprint(dp)

print(ans**2)

