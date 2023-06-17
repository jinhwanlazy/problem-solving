from collections import deque
from heapq import *

N = int(input())
W = [list(map(int, input().split())) for _ in range(N)]

def fill(i, j, v):
    Q = deque([(i, j)])
    v0 = W[i][j]
    W[i][j] = v
    if v0 == v:
        return
    while Q:
        i, j = Q.popleft()
        for di, dj in ((0, 1), (0, -1), (1, 0), (-1, 0)):
            i2, j2 = i + di, j + dj
            if 0 <= i2 < N and 0 <= j2 < N and W[i2][j2] == v0:
                W[i2][j2] = v
                Q.append((i2, j2))
    
def shortest_bridge(i, j):
    visited = [[0] * N for _ in range(N)]
    Q = [(0, i, j)]
    v = W[i][j]
    visited[i][j] = 1
    while Q:
        d, i, j = heappop(Q)
        for di, dj in ((0, 1), (0, -1), (1, 0), (-1, 0)):
            i2, j2 = i + di, j + dj
            if not (0 <= i2 < N and 0 <= j2 < N):
                continue
            if visited[i2][j2]:
                continue
            visited[i2][j2] = 1
            if W[i2][j2] == 0:
                heappush(Q, (d + 1, i2, j2))
            elif W[i2][j2] == v:
                heappush(Q, (d, i2, j2))
            else:
                return d
    return 9999

seeds = []
cnt_island = 1
for i in range(N):
    for j in range(N):
        if W[i][j] == 1:
            cnt_island += 1
            fill(i, j, cnt_island)
            seeds.append((i, j))

ans = 99999
for i, j in seeds:
    ans = min(ans, shortest_bridge(i, j))

print(ans)
