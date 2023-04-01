import sys
from itertools import zip_longest
input = sys.stdin.readline

N = int(input())
ps = iter(sorted((int(input()) for _ in range(N)), reverse=True))
ans = sum(a + b for a, b, _ in zip_longest(ps, ps, ps, fillvalue=0))
print(ans)
