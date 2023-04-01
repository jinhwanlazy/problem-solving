from itertools import combinations
xs = [int(input()) for _ in range(9)]
for idxs in combinations(range(9), 7):
    if sum(xs[i] for i in idxs) == 100:
        print('\n'.join(map(str, (xs[i] for i in idxs))))

