from itertools import permutations
import sys
input = sys.stdin.readline

N = int(input())
genes = set(input().split())
if len(genes) == 1:
    print('1')
    print(max(genes.pop()))
else:
    res = set()
    for l, r in permutations(genes, 2):
        res.add(max(l[0], r[1]))
    print(len(res))
    print(' '.join(sorted(res)))
