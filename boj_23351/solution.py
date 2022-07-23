from heapq import *

N, K, A, B = map(int, input().split())
N //= A
Q = [K] * N
i = 1
while True:
    x = heappop(Q)
    if x < i:
        print(i-1)
        break
    else:
        heappush(Q, x + B)
    i += 1
