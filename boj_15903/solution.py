from heapq import *

N, M = map(int, input().split())
xs = list(map(int, input().split()))

heapify(xs)
for _ in range(M):
    a, b = heappop(xs), heappop(xs)
    c = a + b
    heappush(xs, c)
    heappush(xs, c)

print(sum(xs))

