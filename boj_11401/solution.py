def bino_small(n, k, mod):
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

    def prod(rng, mod):
        res = 1
        for i in rng:
            res *= i
            res %= mod
        return res

    A = prod(range(k+1, n+1), mod)
    B = prod(range(1, n-k+1), mod)
    return (A * pow(B, mod-2, mod)) % mod

MOD = 1000000007
N, K = map(int, input().split())
print(bino_small(N, K, MOD))
