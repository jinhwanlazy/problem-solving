import itertools
N, M, D = map(int, input().split())
enemies = [(i, j) for i in range(N) for j, c in enumerate(input().split()) if c == '1']

def dist(archer):
    return lambda e: (abs(N - e[0]) + abs(archer - e[1]), e[1])

def simulate(archers):
    ess = [sorted(enemies, key=dist(a), reverse=True) for a in archers]
    dead = set()
    s = 0
    while any(ess):
        dead_ = set()
        for a, es in zip(archers, ess):
            while es and (es[-1] in dead or es[-1][0] + s >= N):
                es.pop()
            if es and dist(a)((es[-1][0] + s, es[-1][1]))[0] <= D:
                dead_.add(es[-1])
        dead |= dead_
        s += 1
    return len(dead)

print(max(simulate(A) for A in itertools.combinations(range(M), 3)))
