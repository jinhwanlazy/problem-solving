N = int(input())
grid = [list(input().strip()) for _ in range(N)]

def swapv(i, j):
    grid[i][j], grid[i+1][j] = grid[i+1][j], grid[i][j]

def swaph(i, j):
    grid[i][j], grid[i][j+1] = grid[i][j+1], grid[i][j]
    
def count():
    res = 0
    for row in grid:
        res = max(res, count_row(row))
    for col in zip(*grid):
        res = max(res, count_row(col))
    return res

def count_row(row):
    S = []
    ans = 0
    for c in row:
        if S and S[-1] != c:
            S.clear()
        S.append(c)
        ans = max(ans, len(S))
    return ans

ans = 0
for i in range(N):
    for j in range(N):
        if j < N-1:
            swaph(i, j)
            ans = max(ans, count())
            swaph(i, j)
        if i < N-1:
            swapv(i, j)
            ans = max(ans, count())
            swapv(i, j)

print(ans)
