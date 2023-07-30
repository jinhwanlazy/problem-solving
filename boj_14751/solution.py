import sys
input = sys.stdin.readline

from bisect import bisect
from operator import attrgetter
from dataclasses import dataclass
from decimal import Decimal


# swapping x, y for ease of representation
r, l = map(int, input().split())
n = int(input())
x0, x1 = 0, r - l

@dataclass
class Seg:
    id: int
    y1: int
    y0: int
    x: Decimal = 0

    def slope(self):
        return Decimal(self.y1 - self.y0) / Decimal(x1)

    def intersection(self, other):
        return -Decimal(self.y0 - other.y0) / (self.slope() - other.slope())


segs = [Seg(i + 1, *map(int, input().split())) for i in range(n)]
segs.sort(key=attrgetter('y0'))

hull = [segs[0]]
for i in range(1, n):
    seg = segs[i]
    if hull and hull[-1].slope() <= seg.slope():
        continue
    while hull:
        seg.x = seg.intersection(hull[-1])
        if seg.x < hull[-1].x:
            hull.pop()
        else:
            break
    hull.append(seg)

for _ in range(int(input())):
    x = Decimal(input()) - Decimal(l)
    i = bisect(hull, x, key=attrgetter('x')) - 1
    print(hull[i].id)
    


