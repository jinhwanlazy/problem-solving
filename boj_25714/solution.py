from functools import lru_cache
from itertools import combinations

N = int(input())
MOD = int(1e9 + 7)

@lru_cache(maxsize=None)
def count3(a, b, c):
    if a == b == c == 0:
        return 1
    ans = 0
    if a > 0:
        ans += count3(a-1, b, c)
    if b > 0:
        ans += count3(a, b-1, c)
    if c > 0:
        ans += count3(a, b, c-1)
    return ans % MOD

@lru_cache(maxsize=None)
def count2(a, b):
    if a == b == 0:
        return 1
    ans = 0
    if a > 0:
        ans += count2(a-1, b)
    if b > 0:
        ans += count2(a, b-1)
    return ans % MOD

@lru_cache(maxsize=None)
def count1(a):
    if a <= 1:
        return 1
    if a == 2:
        return 2
    res = 2
    for i in range(1, a-1):
        res += count2(i, a - i - 1)
        res %= MOD
    return res

@lru_cache(maxsize=None)
def dp(a, b, c):
    a, b, c = sorted((a, b, c))
    return (count3(a, b, c) * count1(a) * count1(b) * count1(c)) % MOD
    
ans = 0
for a, b, c in combinations(range(N), 3):
    a, b, c = b - a - 1, c - b - 1, (a - c) % N - 1
    ans += dp(a, b, c)
    ans %= MOD

print(ans)
