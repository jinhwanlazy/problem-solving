'''
Disorderly Escape
=================

Oh no! You've managed to free the bunny workers and escape Commander Lambdas exploding space station, but Lambda's team of elite starfighters has flanked your ship. If you dont jump to hyperspace, and fast, youll be shot out of the sky!

Problem is, to avoid detection by galactic law enforcement, Commander Lambda planted the space station in the middle of a quasar quantum flux field. In order to make the jump to hyperspace, you need to know the configuration of celestial bodies in the quadrant you plan to jump through. In order to do *that*, you need to figure out how many configurations each quadrant could possibly have, so that you can pick the optimal quadrant through which youll make your jump. 

There's something important to note about quasar quantum flux fields' configurations: when drawn on a star grid, configurations are considered equivalent by grouping rather than by order. That is, for a given set of configurations, if you exchange the position of any two columns or any two rows some number of times, youll find that all of those configurations are equivalent in that way -- in grouping, rather than order.

Write a function solution(w, h, s) that takes 3 integers and returns the number of unique, non-equivalent configurations that can be found on a star grid w blocks wide and h blocks tall where each celestial body has s possible states. Equivalency is defined as above: any two star grids with each celestial body in the same state where the actual order of the rows and columns do not matter (and can thus be freely swapped around). Star grid standardization means that the width and height of the grid will always be between 1 and 12, inclusive. And while there are a variety of celestial bodies in each grid, the number of states of those bodies is between 2 and 20, inclusive. The solution can be over 20 digits long, so return it as a decimal string.  The intermediate values can also be large, so you will likely need to use at least 64-bit integers.

For example, consider w=2, h=2, s=2. We have a 2x2 grid where each celestial body is either in state 0 (for instance, silent) or state 1 (for instance, noisy).  We can examine which grids are equivalent by swapping rows and columns.

00
00

In the above configuration, all celestial bodies are "silent" - that is, they have a state of 0 - so any swap of row or column would keep it in the same state.

00 00 01 10
01 10 00 00

1 celestial body is emitting noise - that is, has a state of 1 - so swapping rows and columns can put it in any of the 4 positions.  All four of the above configurations are equivalent.

00 11
11 00

2 celestial bodies are emitting noise side-by-side.  Swapping columns leaves them unchanged, and swapping rows simply moves them between the top and bottom.  In both, the *groupings* are the same: one row with two bodies in state 0, one row with two bodies in state 1, and two columns with one of each state.

01 10
01 10

2 noisy celestial bodies adjacent vertically. This is symmetric to the side-by-side case, but it is different because there's no way to transpose the grid.

01 10
10 01

2 noisy celestial bodies diagonally.  Both have 2 rows and 2 columns that have one of each state, so they are equivalent to each other.

01 10 11 11
11 11 01 10

3 noisy celestial bodies, similar to the case where only one of four is noisy.

11
11

4 noisy celestial bodies.

There are 7 distinct, non-equivalent grids in total, so solution(2, 2, 2) would return 7.

Languages
=========

To provide a Java solution, edit Solution.java
To provide a Python solution, edit solution.py

Test cases
==========
Your code should pass the following test cases.
Note that it may also be run against hidden test cases not shown here.

-- Java cases --
Input:
Solution.solution(2, 3, 4)
Output:
    430

Input:
Solution.solution(2, 2, 2)
Output:
    7

-- Python cases --
Input:
solution.solution(2, 3, 4)
Output:
    430

Input:
solution.solution(2, 2, 2)
Output:
    7
'''
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
