import sys
from itertools import combinations
input = sys.stdin.readline

N, K = map(int, input().split())

if K < 5:
    ans = 0
else:
    antic = set('antic')
    words = [set(input().strip()) - antic for _ in range(N)]
    chars = set().union(*words)
    if K == 5:
        ans = sum(len(w) == 0 for w in words)
    else:
        c = combinations(chars, min(len(chars), K - 5))
        ans = max(sum(map(set(s).issuperset, words)) for s in c)
        
print(ans)
