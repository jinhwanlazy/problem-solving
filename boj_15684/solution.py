from itertools import combinations

N, M, H = map(int, input().split())

edges = list(tuple(map(int, input().split())) for _ in range(M))
edges_to_exclude = set()
for a, b in edges:
    edges_to_exclude.add((a, b))
    edges_to_exclude.add((a, b-1))
    edges_to_exclude.add((a, b+1))
    
cands = [(a, b) for a in range(1, H+1) for b in range(1, N) if (a, b) not in edges_to_exclude]

def simulate(edges):
    xs = list(range(N))
    for a, b in sorted(edges):
        xs[b-1], xs[b] = xs[b], xs[b-1]
    return xs == list(range(N))

def interfere(edges):
    for (a1, b1), (a2, b2) in combinations(edges, 2):
        if a1 == a2 and abs(b1 - b2) == 1:
            return True
    return False

def solve():
    if simulate(edges):
        return 0

    for n_new_edge in range(1, 4):
        for new_edges in combinations(cands, n_new_edge):
            if interfere(new_edges):
                continue
            if simulate(list(edges) + list(new_edges)):
                return n_new_edge
    return -1
    
print(solve())

