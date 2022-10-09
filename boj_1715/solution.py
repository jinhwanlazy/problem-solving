from heapq import *
C = [int(input()) for _ in range(int(input()))]
heapify(C)
ans = 0
while len(C) > 1:
    a, b = heappop(C), heappop(C)
    ans += a + b
    heappush(C, a + b)
print(ans)
