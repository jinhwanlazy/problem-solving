from heapq import *
import sys
input = sys.stdin.readline

T = 0
while True:
    T += 1
    N = int(input())
    if N == 0:
       break 
    W = [list(map(int, input().split())) for _ in range(N)]

    Q = [(W[0][0], 0, 0)]
    D = [[1e9] * N for _ in range(N)]
    D[0][0] = W[0][0]

    while Q:
        d, i, j = heappop(Q)
        for ii, jj in ((i, j+1), (i+1, j), (i, j-1), (i-1, j)):
            if not (0 <= ii < N and 0 <= jj < N):
                continue
            dd = d + W[ii][jj]
            if D[ii][jj] > dd:
                D[ii][jj] = dd
                heappush(Q, (dd, ii, jj))

    print(f'Problem {T}: {D[N-1][N-1]}')
