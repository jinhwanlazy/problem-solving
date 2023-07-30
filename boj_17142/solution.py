from copy import deepcopy
from itertools import combinations
INF = 9876543210
N, M = map(int, input().split())
A = [list(map(int, input().split())) for _ in range(N)]
ans = INF

seeds = []
for i, row in enumerate(A):
    for j, c in enumerate(row):
        if c == 0:
            A[i][j] = INF
        elif c == 1:
            A[i][j] = -1
        elif c == 2:
            seeds.append((i, j))
            A[i][j] = 0

def simulate(virus, A):
    global ans
    step = 0
    visited = set()
    for i, j in virus:
        A[i][j] = step
    while virus:
        if step >= ans:
            return
        step += 1
        virus_swap = set()
        for (i, j) in virus:
            visited.add((i, j))
            for (ii, jj) in ((i, j + 1), (i, j - 1), (i + 1, j), (i - 1, j)):
                if not (0 <= ii < N and 0 <= jj < N):
                    continue
                if A[ii][jj] <= step:
                    if A[ii][jj] == 0:
                        virus_swap.add((ii, jj))
                    continue
                A[ii][jj] = step
                virus_swap.add((ii, jj))
        virus = [v for v in list(virus_swap) if v not in visited]
    res = max(A[i][j] for i in range(N) for j in range(N) if A[i][j] != 1000)
    ans = min(ans, res)
    # return max(A[i][j] for i in range(N) for j in range(N) if A[i][j] != 1000)

for virus in combinations(seeds, M):
    simulate(virus, deepcopy(A))
print(ans if ans != INF else -1)
