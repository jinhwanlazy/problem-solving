from collections import deque

INF = 987654321
N = int(input())

visited = set()
def solve():
    Q = deque([(0, 1, 0)])
    while Q:
        d, n, c = Q.popleft()
        if n == N:
            return d

        nxt_states = [(n - 1, c), (n + c, c), (n, n)]
        for nxt in nxt_states:
            if nxt not in visited:
                visited.add(nxt)
                Q.append((d + 1, ) + nxt)

print(solve())
