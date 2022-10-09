from collections import deque

N, M = map(int, input().split())
grid = [list(map(int, input().split())) for _ in range(N)]

def get_neighbors(i, j):
    for ii, jj in ((i, j + 1), (i, j - 1), (i + 1, j), (i - 1, j)):
        yield ii, jj

def get_shores():
    res = []
    for i, row in enumerate(grid):
        for j, x in enumerate(row):
            if x == 0: 
                continue
            n_waters = sum(grid[ii][jj] == 0 for ii, jj in get_neighbors(i, j))
            if n_waters > 0:
                res.append((i, j, n_waters))
    return res 

def count_islands():
    visited = [[0] * M for _ in range(N)]
    c = 0
    for i, row in enumerate(grid):
        for j, v in enumerate(row):
            if v == 0 or visited[i][j] > 0: 
                continue
            c += 1
            Q = deque()
            Q.append((i, j))
            visited[i][j] = c
            while Q:
                y, x = Q.popleft()
                for yy, xx in get_neighbors(y, x):
                    if grid[yy][xx] == 0 or visited[yy][xx] > 0:
                        continue
                    visited[yy][xx] = c
                    Q.append((yy, xx))
    return c
    
year = 0
n_islands = count_islands()
while n_islands == 1:
    shores = get_shores()
    if not shores:
        break
    year += 1
    for i, j, c in shores:
        grid[i][j] = max(0, grid[i][j] - c)
    n_islands = count_islands()

if n_islands > 1:
    print(year)
else:
    print(0)
