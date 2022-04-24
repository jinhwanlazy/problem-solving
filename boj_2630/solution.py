def solve(grid, color):
    if len(grid) == 1:
        return grid[0][0] == color

    all_same = True
    for row in grid:
        for x in row:
            all_same &= x == color

    if all_same:
        return 1

    l = len(grid) // 2
    A = [row[:l] for row in grid[:l]]
    B = [row[l:] for row in grid[:l]]
    C = [row[:l] for row in grid[l:]]
    D = [row[l:] for row in grid[l:]]
    return sum(solve(subgrid, color) for subgrid in (A, B, C, D))
    
N = int(input())
grid = [list(map(int, input().split())) for _ in range(N)]
print(solve(grid, 0))
print(solve(grid, 1))
