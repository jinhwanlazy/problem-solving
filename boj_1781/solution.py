import sys
from operator import itemgetter
input = sys.stdin.readline

N = int(input())
lecs = sorted((tuple(map(int, input().split())) for _ in range(N)),
              reverse=True, key=itemgetter(1))
days = list(range(0, 200001))

def find_empty(i):
    if days[i] == i:
        return i
    days[i] = find_empty(days[i])
    return days[i]

def fill(i):
    i = find_empty(i)
    if i != 0:
        return False
    days[i] = find_empty(i-1)
    return True

ans = 0
for d, p in lecs:
    i = find_empty(d)
    if i != 0:
        ans += p
        days[i] -= 1

print(ans)
