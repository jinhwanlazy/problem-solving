from itertools import combinations
N = int(input())
P = list(map(int, input().split()))
G = [[] for _ in range(N)]
for i in range(N):
    js = list(map(int, input().split()))
    for j in js[1:]:
        j -= 1
        G[i].append(j)
        G[j].append(i)

def all_connected(group):
    ufs = list(range(N))

    def find(i):
        return ufs[i]

    def union(i, j):
        i, j = find(i), find(j)
        if i == j:
            return
        for k in range(N):
            if find(k) == j:
                ufs[k] = i

    for i, j in combinations(group, 2):
        if j in G[i]:
            union(i, j)

    g = find(group[0])
    return all(g == find(i) for i in group[1:])


def check(group):
    non_group = [i for i in range(N) if i not in group]
    return all_connected(group) and all_connected(non_group)

def diff(group):
    a = sum(P[i] for i in group)
    b = sum(P[i] for i in range(N) if i not in group)
    return abs(a - b)

INF = 999999999
ans = INF
for i in range(1, N // 2 + 1):
    for group in combinations(range(N), i):
        if check(group):
            ans = min(ans, diff(group))
print(-1 if ans == INF else ans)


