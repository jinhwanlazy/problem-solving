import sys
input = sys.stdin.readline

N, M, K = map(int, input().split())
A = list(map(int, input().split()))

parents = [[] for _ in range(N)]
for _ in range(M):
    u, v = map(int, input().split())
    u -= 1
    v -= 1
    parents[v].append(u)

INF = 987654321
dp = [[INF] * K for _ in range(N)]
for i in range(N):
    dp[i][0] = A[i]

for i in range(1, K):
    for v in range(N):
        for u in parents[v]:
            if dp[u][i-1] != INF:
                dp[v][i] = max(dp[v][i], dp[u][i-1])

if all(row[-1] == INF for row in dp):
    print(-1)
else:
    ans = min(row[-1] for row in dp if row[-1] != -1)
    print(ans)

from pprint import pprint
pprint(dp)
