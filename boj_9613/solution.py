from math import gcd
from itertools import combinations
for _ in range(int(input())):
    xs = list(map(int, input().split()))[1:]
    ans = sum(gcd(a, b) for a, b in combinations(xs, 2))
    print(ans)
    
