from pprint import pprint
import itertools as it

def preimages_of_a_cell(cell):
    return {
        True: (
            (0, 1),
            (0, 2),
            (1, 0),
            (2, 0),
        ),
        False: (
            (0, 0),
            (0, 3),
            (1, 1),
            (1, 2),
            (1, 3),
            (2, 1),
            (2, 2),
            (2, 3),
            (3, 0),
            (3, 1),
            (3, 2),
            (3, 3),
        )
    }[cell]

def preimages_of_a_row(row):
    def encode(path):
        a, b = 0, 0
        for i, j in path:
            a = (a << 1) | ((i & 2) >> 1)
            b = (b << 1) | (i & 1)
        last = path[-1][-1]
        a = (a << 1) | ((last & 2) >> 1)
        b = (b << 1) | (last & 1)
        return (a, b)

    res = []
    stack = [(0, tuple())]
    while stack:
        idx, path = stack.pop()
        if idx == len(row):
            res.append(encode(path))
        else:
            for pre in preimages_of_a_cell(row[idx]):
                if not path or path[-1][-1] == pre[0]:
                    stack.append((idx+1, path + (pre, )))
    return res

def count_preimages(grid):
    preimages = [preimages_of_a_row(row) for row in grid]
    counter = [[1 if i == 0 else 0]*len(pre) for i, pre in enumerate(preimages)]

    for i, cand in enumerate(preimages):
        if i == 0:
            continue
        for j, pre in enumerate(cand):
            for k, prev in enumerate(preimages[i-1]):
                if prev[-1] == pre[0]:
                    counter[i][j] += counter[i-1][k]
    return sum(counter[-1])

def transpose(grid):
    return list(map(list, zip(*grid)))

def show_grid(grid):
    for row in grid:
        line = []
        for cell in row:
            line.append('#' if cell else '-')
        print ''.join(line)

def solution(g):
    g = transpose(g)
    #  show_grid(g)
    return count_preimages(g)

if __name__ == '__main__':
    print(solution(input()))
