import sys
from collections import deque
input = sys.stdin.readline
N, M, K, X = map(int, input().split())

G = [[] for _ in range(N)]
for _ in range(int(M)):
    A, B = map(int, input().split())
    G[A-1].append(B-1)

Q = deque()
Q.append((0, X-1))
V = [0] * N
V[X-1] = 1
ans = []
while Q:
    d, i = Q.popleft()
    for j in G[i]:
        if V[j]:
            continue
        V[j] = 1
        if d + 1 == K:
            ans.append(j+1)
            continue
        else:
            Q.append((d + 1, j))

if not ans:
    print(-1)
else:
    print('\n'.join(map(str, sorted(ans))))
    
    
