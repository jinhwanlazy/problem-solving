from itertools import combinations
N, M = map(int, input().split())
xs = sorted(map(int, input().split()))

seen = set()
for res in combinations(xs, M):
    if res in seen:
        continue
    seen.add(res)
    print(' '.join(map(str, res)))
