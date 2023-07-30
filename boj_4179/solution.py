import sys
input = sys.stdin.readline

def main():
    h, w = map(int, input().split())
    W = [list(input().strip()) for _ in range(h)]
    fires = set()
    sks = set()
    for i, row in enumerate(W):
        for j, c in enumerate(row):
            if c == 'F':
                fires.add((i, j))
            if c == 'J':
                sks.add((i, j))

    def bound_check(i, j):
        return 0 <= i < h and 0 <= j < w

    def dirs(i, j):
        return (i, j + 1), (i, j - 1), (i + 1, j), (i-1, j)

    def is_escape(i, j):
        return not bound_check(i, j)


    step = 0
    visited = set()
    while sks:
        step += 1
        sks_swap = set()
        for i, j in sks:
            if W[i][j] == 'F':
                continue
            for ii, jj in dirs(i, j):
                if is_escape(ii, jj):
                    return step
                if not bound_check(ii, jj):
                    continue
                if (ii, jj) in visited:
                    continue
                if W[ii][jj] != '.':
                    continue
                visited.add((ii, jj))
                sks_swap.add((ii, jj))
        sks = sks_swap
        fires_swap = set()
        for i, j in fires:
            for ii , jj in dirs(i, j):
                if not bound_check(ii, jj):
                    continue
                if W[ii][jj] not in '.J':
                    continue
                W[ii][jj] = 'F'
                fires_swap.add((ii, jj))
        fires = fires_swap
    return 'IMPOSSIBLE'
        
ans = main()
print(ans)
