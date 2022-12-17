from functools import lru_cache

N = int(input())
pos = []
neg = []
zero = 0
one = 0

for _ in range(N):
    i = int(input())
    if i == 0:
        zero += 1
    elif i == 1:
        one += 1
    elif i > 0:
        pos.append(i)
    else:
        neg.append(i)
pos.sort(reverse=True)
neg.sort()

ans = 0
ans += one
for i in range(0, len(pos)-1, 2):
    ans += pos[i] * pos[i+1]
if len(pos) % 2 == 1:
    ans += pos[-1]
for i in range(0, len(neg)-1, 2):
    ans += neg[i] * neg[i+1]
if len(neg) % 2 == 1:
    if zero == 0:
        ans += neg[-1]
print(ans)
