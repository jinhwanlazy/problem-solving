from collections import deque

N, M = map(int, input().split())
grid = [list(map(int, input().split())) for _ in range(N)]

def neighbors(i, j):
    for ii, jj in ((i, j + 1), (i, j - 1), (i + 1, j), (i - 1, j)):
        if 0 <= ii < N and 0 <= jj < M:
            yield ii, jj

def get_borders():
    borders = []
    for i, row in enumerate(grid):
        for j, x in enumerate(row):
            if grid[i][j] == 0: 
                continue
            n_waters = sum(grid[ii][jj] == 0 for ii, jj in neighbors(i, j))
            if n_waters > 0:
                borders.append((i, j, n_waters))
    return borders

def count_islands():
    visited = [[0] * M for _ in range(N)]
    c = 0
    for i, row in enumerate(grid):
        for j, x in enumerate(row):
            if grid[i][j] == 0 or visited[i][j] > 0: 
                continue
            c += 1
            Q = deque()
            Q.append((i, j))
            visited[i][j] = c
            while Q:
                i, j = Q.popleft()
                for ii, jj in neighbors(i, j):
                    if grid[ii][jj] == 0 or visited[ii][jj] != 0:
                        continue
                    visited[ii][jj] = c
                    Q.append((ii, jj))
    return c
    
year = 0
while count_islands() == 1:
    borders = get_borders()
    if not borders:
        break
    year += 1
    for i, j, c in borders:
        grid[i][j] = max(0, grid[i][j] - c)
if count_islands() > 1:
    print(year)
else:
    print(0)
