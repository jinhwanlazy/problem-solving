import itertools as it
from math import factorial
from collections import Counter

def identity_action(w, h):
    return [[r * w + c for c in range(w)] for r in range(h)]

def gen_rowwise_actions(w, h, grid=None):
    if grid is None:
        grid = identity_action(w, h)
    for perm in it.permutations(range(h)):
        yield [grid[i] for i in perm]

def gen_colwise_actions(w, h, grid=None):
    if grid is None:
        grid = identity_action(w, h)
    for perm in it.permutations(range(w)):
        yield [[row[c] for c in perm] for row in grid]

def gen_actions(w, h):
    for grid1 in gen_rowwise_actions(w, h):
        for grid2 in gen_colwise_actions(w, h, grid1):
            yield grid2

def count_unique_orbits(action):
    w, h = len(action[0]), len(action)
    visit = [[None] * w for _ in range(h)]
    for i in range(w * h):
        j = i
        while True:
            r, c = j / w, j % w
            if visit[r][c] is not None:
                break
            visit[r][c] = i
            j = action[r][c]
            if j == i:
                break
    return len(set(i for row in visit for i in row))

def bruteforce_solution(w, h, s):
    G = total_actions = factorial(w) * factorial(h)
    return str(sum(s**count_unique_orbits(a) for a in gen_actions(w, h)) / G)

def drop1(lst):
    return [v for v in lst if v != 1]

def gen_cycle_types_of_perm(n):
    if n == 0:
        return {tuple()}
    res = set()
    for i in range(1, n+1):
        for g in gen_cycle_types_of_perm(n-i):
            res.add(tuple(sorted((i, ) + g)))
    return res

def shift_rows(grid, top, bottom):
    tmp = grid[top]
    for r in range(top, bottom-1):
        grid[r] = grid[r+1]
    grid[bottom-1] = tmp
    return grid

def transpose(grid):
    return list(map(list, zip(*grid)))

def shift_cols(grid, left, right):
    grid = transpose(grid)
    grid = shift_rows(grid, left, right)
    return transpose(grid)

def create_a_action_from_cycle_type(row_cycles, col_cycles):
    grid = identity_action(sum(col_cycles), sum(row_cycles))
    r = 0
    for dr in row_cycles:
        grid = shift_rows(grid, r, r+dr)
        r += dr
    c = 0
    for dc in col_cycles:
        grid = shift_cols(grid, c, c+dc)
        c += dc
    return grid

def count_unique_orbits_by_cycle_types(row_cycles, col_cycles):
    action = create_a_action_from_cycle_type(row_cycles, col_cycles)
    return count_unique_orbits(action)

def count_permutations_by_cycle_type(cycles):
    n = sum(cycles)
    res = 1
    for k in cycles:
        res *= factorial(n) / factorial(n-k) / k
        n -= k
    for dup in Counter(cycles).values():
        res /= factorial(dup)
    return res

def solution(w, h, s):
    rowwise_cycle_types = gen_cycle_types_of_perm(h)
    colwise_cycle_types = gen_cycle_types_of_perm(w)
    res = 0
    for row_cycles in rowwise_cycle_types:
        for col_cycles in colwise_cycle_types:
            a = count_permutations_by_cycle_type(row_cycles)
            b = count_permutations_by_cycle_type(col_cycles)
            c = count_unique_orbits_by_cycle_types(row_cycles, col_cycles)
            res += (a * b) * s**c
    G = total_actions = factorial(w) * factorial(h)
    return str(res / G)

if __name__ == '__main__':
    print(solution(*input()))
