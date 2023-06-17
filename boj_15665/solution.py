from itertools import product
N, M = map(int, input().split())
xs = sorted(set(map(int, input().split())))

for p in product(xs, repeat=M):
    print(' '.join(map(str, p)))
