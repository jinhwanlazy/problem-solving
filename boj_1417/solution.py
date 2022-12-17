import sys
from heapq import *

N = int(input())
x = int(input())
ys = [-int(input()) for _ in range(N-1)]

if not ys:
    print(0)
    sys.exit(0)

heapify(ys)
count = 1
while True:
    y = -heappop(ys)
    if x > y:
        break
    x += 1
    y -= 1
    count += 1
    heappush(ys, -y)
print(count - 1)





