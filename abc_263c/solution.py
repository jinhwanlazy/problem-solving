from itertools import combinations

N, M = map(int, input().split())
for seq in combinations(range(1, M+1), N):
    print(' '.join(map(str, seq)))
