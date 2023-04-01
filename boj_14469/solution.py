N = int(input())

t = 0
for s, e in sorted(tuple(map(int, input().split())) for _ in range(N)):
    if s > t:
        t = s + e
    else:
        t += e

print(t)
