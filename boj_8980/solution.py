from dataclasses import dataclass
import sys
input = sys.stdin.readline

@dataclass
class Package:
    start: int
    end: int
    amount: int

N, C = map(int, input().split())
M = int(input())
ps = [Package(*map(int, input().split())) for _ in range(M)]
# ps.sort(key=lambda p: (Package.travel, p.end, p.start))
ps.sort(key=lambda p: p.end)

ans = 0
bandwidth = [C] * (N + 1)
for p in ps:
    available = min(min(bandwidth[p.start:p.end]), p.amount)
    if available == 0:
        continue
    for i in range(p.start, p.end):
        bandwidth[i] -= available
    ans += available
print(ans)
