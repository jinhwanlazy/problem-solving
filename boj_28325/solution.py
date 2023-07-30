N = int(input())
A = list(map(int, input().split()))

# case 1. no ant occupies 0th cave
dp = [[0] * N for _ in range(2)]
dp[0][0] = A[0]
dp[1][0] = -99999999999999
for i in range(1, N):
    dp[0][i] = max(dp[0][i-1] + A[i], dp[1][i-1] + A[i])
    dp[1][i] = dp[0][i-1] + 1
ans = max(dp[0][N-1], dp[1][N-1])

# case 2. ans ant occupies 0th cave
dp = [[0] * N for _ in range(2)]
dp[0][0] = -999999999999999
dp[1][0] = 1
for i in range(1, N):
    dp[0][i] = max(dp[0][i-1] + A[i], dp[1][i-1] + A[i])
    dp[1][i] = dp[0][i-1] + 1
ans = max(ans, dp[0][N-1])
print(ans)

