import sys
from operator import itemgetter

input = sys.stdin.readline

N = int(input())
dws = [tuple(map(int, input().split())) for _ in range(N)]
dws.sort(key=itemgetter(1), reverse=True)

bins = [0] * 1001

for d, w in dws:
    while d > 0 and bins[d] != 0:
        d -= 1
    if d != 0:
        bins[d] = w
print(sum(bins))
