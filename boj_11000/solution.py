import sys
from heapq import *
input = sys.stdin.readline

cs = []
for _ in range(int(input())):
    s, e = map(int, input().split())
    cs.append((s, e))
cs.sort()

bins = []
for s, e in cs:
    if not bins:
        bins.append(e)
        continue
    pe = heappop(bins)
    if pe <= s:
        heappush(bins, e)
    else:
        heappush(bins, pe)
        heappush(bins, e)

print(len(bins))


