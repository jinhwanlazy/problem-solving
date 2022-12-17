import sys
input = sys.stdin.readline

R, C = map(int, input().split())
W = [list(input().strip()) for _ in range(R)]

def dfs(i, j):
    if j == C-1:
        W[i][j] = 'o'
        return True
    for di in [-1, 0, 1]:
        ii = i + di
        if ii < 0 or R <= ii or W[ii][j+1] != '.':
            continue
        W[i][j] = '!'
        if dfs(ii, j+1):
            return True
    return False
    

for r in range(R):
    dfs(r, 0)

# from pprint import pprint
# pprint(W)

ans = sum(W[r][C-1] == 'o' for r in range(R))
print(ans)
