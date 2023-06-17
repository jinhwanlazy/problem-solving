n, m = map(int, input().split())
W = [list(map(int, input().split())) for _ in range(n)]

for i in range(n):
    for j in range(m):
        if W[i][j] == 2:
            break
    else:
        continue
    break

from collections import deque
Q = deque(((i, j, 0), ))
distance = [[-1] * m for _ in range(n)]
distance[i][j] = 0
while Q:
    i, j, d = Q.popleft()
    for ii, jj in ((i + 1, j), (i - 1, j), (i, j + 1), (i, j - 1)):
        if not (0 <= ii < n and 0 <= jj < m) or distance[ii][jj] >= 0 or W[ii][jj] == 0:
            continue
        distance[ii][jj] = d + 1
        Q.append((ii, jj, d + 1))

for i, row in enumerate(distance):
    for j, d in enumerate(row):
        if d == -1 and W[i][j] == 0:
            distance[i][j] = 0
    print(' '.join(map(str, row)))

        
    

