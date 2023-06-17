from collections import deque

N, M = map(int, input().split())
W = [input().split() for _ in range(N)]

def floodfill(i, j):
    Q = deque()
    Q.append((i, j))
    res = 0
    while Q:
        i, j = Q.popleft()
        if W[i][j] != '1':
            continue
        res += 1
        W[i][j] = '2'
        for di, dj in ((0, 1), (0, -1), (1, 0), (-1, 0)):
            ii = i + di
            jj = j + dj
            if not (0 <= ii < N and 0 <= jj < M):
                continue
            if W[ii][jj] == '1':
                Q.append((ii, jj))
    return res
    
cnt = 0
ans = 0
for i, row in enumerate(W):
    for j, c in enumerate(row):
        if c == '1':
            cnt += 1
            ans = max(ans, floodfill(i, j))
        
print(cnt)
print(ans)
