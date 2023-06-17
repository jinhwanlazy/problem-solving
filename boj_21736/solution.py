N, M = map(int, input().split())
W = [input() for _ in range(N)]

def find_I():
    for i, row in enumerate(W):
        for j, c in enumerate(row):
            if c == 'I':
                return i, j

i, j = find_I()
visited = [[0] * M for _ in range(N)]

from collections import deque
Q = deque([(i, j)])
visited[i][j] = 1
cnt = 0
while Q:
    i, j = Q.pop()
    for ii, jj in ((i, j+1), (i, j-1), (i+1, j), (i-1, j)):
        if not (0 <= ii < N and 0 <= jj < M) or visited[ii][jj] or W[ii][jj] == 'X':
            continue
        visited[ii][jj] = 1
        cnt += W[ii][jj] == 'P'
        Q.append((ii, jj))

if cnt == 0:
    print('TT')
else:
    print(cnt)

