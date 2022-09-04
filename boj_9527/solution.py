N, M = map(int, input().split())

def count1(n):
    def count1_(n, p):
        if p == 0:
            return (n + 1) // 2
        k = 1 << p
        res = n // (k << 1) * k 
        res += max(0, n - res * 2 - k + 1)
        return res
    res = 0
    p = 0
    while 2**p <= n:
        res += count1_(n, p)
        p += 1
    return res

ans = count1(M) - count1(N-1)
print(ans)
