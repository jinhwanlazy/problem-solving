from functools import lru_cache

# Lucas' theorem
def bino(n, k, mod):
    def decompose(n, mod):
        res = []
        while n:
            res.append(n % mod)
            n //= mod
        return res

    res = 1
    ns = decompose(n, mod)
    ks = decompose(k, mod)
    for a, b in zip(ns, ks):
        res *= bino_small[a][b]
        res %= mod
    return res
    
N, K, M = map(int, input().split())

bino_small = [[0] * 2001 for _ in range(2001)]
bino_small[0][0] = 1
for n in range(1, 2001):
    for k in range(n+1):
        if k == 0 or n == k:
            bino_small[n][k] = 1
        elif n < k:
            bino_small[n][k] = 0
        else:
            bino_small[n][k] = bino_small[n-1][k] + bino_small[n-1][k-1]
            bino_small[n][k] %= M

ans = bino(N, K, M)
print(ans)

