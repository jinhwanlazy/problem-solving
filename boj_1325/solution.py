import sys
from collections import deque

input = sys.stdin.readline

N, M = map(int, input().split())

G = [[] for _ in range(N)]
for _ in range(M):
    a, b = map(int, input().split())
    G[b-1].append(a-1)

def dfs(root):
    Q = deque([root])
    visited = [0] * N
    visited[root] = 1
    while Q:
        i = Q.popleft()
        for j in G[i]:
            if not visited[j]:
                visited[j] = 1
                Q.append(j)
    return sum(visited)

n_children = [dfs(i) for i in range(N)]
max_children = max(n_children)
ans = ' '.join([str(i+1) for i in range(N) if n_children[i] == max_children])
print(ans)
