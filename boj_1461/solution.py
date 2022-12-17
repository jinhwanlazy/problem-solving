N, M = map(int, input().split())
xs = map(int, input().split())
pos, neg = [], []
for x in xs:
    if x >= 0:
        pos.append(x)
    else:
        neg.append(-x)

pos.sort(reverse=True)
neg.sort(reverse=True)

def group_by(xs, n):
    res = [[]]
    for x in xs:
        if len(res[-1]) == n:
            res.append([])
        res[-1].append(x)
    return res

pos = group_by(pos, M)
neg = group_by(neg, M)

def cost(groups, comeback=False):
    res = sum(g[0] * 2 for g in groups if g)
    if groups[0] and not comeback:
        res -= groups[0][0]
    return res

ans = min(
    cost(pos, True) + cost(neg),
    cost(neg, True) + cost(pos)
)

print(ans)
