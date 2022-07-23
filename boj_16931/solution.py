import sys
input = sys.stdin.readline

N, M = map(int, input().split())
W = [list(map(int, input().split())) for _ in range(N)]

ans = 0
for i, row in enumerate(W):
    for j, h in enumerate(row):
        for k in range(h):
            ans += k == 0
            ans += k == h - 1
            ans += i == 0 or W[i-1][j] <= k
            ans += i == N - 1 or W[i+1][j] <= k
            ans += (j == 0) | (W[i][j-1] <= k)
            ans += j == M - 1 or W[i][j+1] <= k
print(ans)
    
