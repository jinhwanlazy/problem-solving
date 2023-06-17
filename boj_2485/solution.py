import sys
input = sys.stdin.readline

import math

N = int(input())
xs = sorted(int(input()) for _ in range(N))
diffs = [b - a for a, b in zip(xs, xs[1:])]

min_diff = min(diffs)
max_diff = max(diffs)

g = diffs[0]
for diff in diffs:
    g = math.gcd(g, diff)

ans = 0
for diff in diffs:
    ans += diff // g - 1

print(ans)
    
    

