from functools import lru_cache

@lru_cache(maxsize=None)
def solve1(n):
    if n in (1, 2):
        return 1
    return solve1(n-1) + solve1(n-2)

def solve2(n):
    return max(n - 2, 0)

n = int(input())
print(solve1(n), solve2(n))
    
