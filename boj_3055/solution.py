from collections import deque

R, C = map(int, input().split())
grid = [list(input()) for _ in range(R)]

Q = deque()

for i, row in enumerate(grid):
    for j, x in enumerate(row):
        if x == 'S':
            Q.append((i, j, 0, x))

for i, row in enumerate(grid):
    for j, x in enumerate(row):
        if x == '*':
            Q.append((i, j, 0, x))

while Q:
    i, j, count, x = Q.popleft()
    if x == 'S':
        if grid[i][j] == 'D':
            print(count)
            break
        if grid[i][j] == '*':
            continue
        for di, dj in ((-1, 0), (1, 0), (0, 1), (0, -1)):
            ii = i + di
            jj = j + dj
            if not (0 <= ii < R and 0 <= jj < C):
                continue
            if grid[ii][jj] in '.D':
                if grid[ii][jj] == '.':
                    grid[ii][jj] = 'S'
                Q.append((ii, jj, count+1, x))
    if x == '*':
        for di, dj in ((-1, 0), (1, 0), (0, 1), (0, -1)):
            ii = i + di
            jj = j + dj
            if not (0 <= ii < R and 0 <= jj < C):
                continue
            if grid[ii][jj] in '.S':
                grid[ii][jj] = '*'
                Q.append((ii, jj, count+1, x))
    # print(i, j, count, x)
    # print('\n'.join(''.join(row) for row in grid))
    # print('-------------------------------------')
else:
    print('KAKTUS')
    
        

    
