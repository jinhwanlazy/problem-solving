from fractions import Fraction
import math
from collections import Counter, defaultdict, deque
import sys
input = sys.stdin.readline

N = int(input())
A = tuple(input().strip() for _ in range(N))
K = int(input())

digit_rems = tuple((10**len(a)) % K for a in A)
A = tuple(map(int, A))
rems = tuple(a % K for a in A)

END = (1 << N)

dp = [[0]*K for _ in range(1 << N)] 
Q = deque()
for i in range(N):
    mask = 1 << i
    dp[mask][rems[i]] = 1
    Q.append(mask)

seen = set()
while Q:
    mask = Q.popleft()
    if mask in seen:
        continue
    seen.add(mask)
    for j in range(N):
        if mask >> j & 1:
            continue
        new_mask = mask | (1 << j)
        for rem in range(K):
            dp[new_mask][(rem * digit_rems[j] + rems[j]) % K] += dp[mask][rem]
        Q.append(new_mask)
res = dp[-1]

f = Fraction(res[0], sum(res))
print('{}/{}'.format(*f.as_integer_ratio()) )
