W, N = input().split()
N = int(N)

grid = [input().split() for _ in range(N)]

if W in 'UD':
    grid = grid[::-1]
elif W in 'LR':
    grid = [row[::-1] for row in grid]

swap = {
    '1': '1',
    '8': '8',
    '5': '2',
    '2': '5',
}

for i, row in enumerate(grid):
    for j, c in enumerate(row):
        grid[i][j] = swap.get(c, '?')

print('\n'.join([' '.join(row) for row in grid]))
