def prod(rng, mod):
    res = 1
    for i in rng:
        res *= i
        res %= mod
    return res

def pow(a, b, mod):
    if (b == 0):
        return 1 % mod
    if (b == 1):
        return a % mod
    res = pow(a, b // 2, mod)
    res *= res
    if b % 2 == 1:
        res *= a
    return res % mod

MOD = 1000000007
N, K = map(int, input().split())
A = prod(range(K+1, N+1), MOD)
B = prod(range(1, N-K+1), MOD)
ans = A * pow(B, MOD-2, MOD)

print(ans % MOD)
