def distance2(a, b):
    return sum(i != j for i, j in zip(a, b))

def distance3(a, b, c):
    return distance2(a, b) + distance2(b, c) + distance2(c, a)

from itertools import combinations, starmap
from collections import Counter
    
for T in range(int(input())):
    N = int(input())
    xs = input().split()
    cnt = Counter(xs)
    if any(c >= 3 for c in cnt.values()):
        print(0)
    else:
        ans = min(starmap(distance3, combinations(xs, 3)))
        print(ans)
        
