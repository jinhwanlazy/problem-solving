from functools import lru_cache

@lru_cache(maxsize=None)
def bino(N, K):
    if K <= 0:
        return 1
    if N <= K:
        return 1
    return bino(N-1, K) + bino(N-1, K-1)

print(bino(*map(int, input().split())))
