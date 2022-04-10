def render(x, y):
    rank = max(abs(x), abs(y))
    side = rank * 2 + 1
    area = side * side

    res = area
    if y == rank:
        return res + x - rank
    res -= side - 1
    if x == -rank:
        return res + y - rank
    res -= side - 1
    if y == -rank:
        return res - x - rank
    res -= side - 1
    return res - y - rank

r1, c1, r2, c2 = map(int, input().split())
grid = [[render(x, y) for x in range(c1, c2+1)] for y in range(r1, r2+1)]
max_len = max(len(str(n)) for row in grid for n in row)
print('\n'.join(' '.join([str(n).rjust(max_len) for n in row]) for row in grid))
