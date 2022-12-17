import sys
input = sys.stdin.readline

N = int(input())
lecs = sorted((tuple(map(int, input().split())) for _ in range(N)), reverse=True)
days = list(range(0, 10001))

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
for p, d in lecs:
    i = find_empty(d)
    if i != 0:
        ans += p
        days[i] -= 1

print(ans)

