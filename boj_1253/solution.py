from collections import Counter
N = int(input())
xs = sorted(map(int, input().split()))
counter = Counter(xs)
ans = 0
for i, x in enumerate(xs):
    # x = a + b
    for a in counter:
        b = x - a
        if counter[a] == 0 or counter[b] == 0:
            continue
        if (a == x or b == x) and not counter[x] >= 2:
            continue
        if x == 0 and (a == x or b == x) and not counter[x] >= 3:
            continue
        if a == b and not counter[a] >= 2:
            continue
        ans += 1
        break
print(ans)

