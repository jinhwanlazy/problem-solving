n = int(input())
dp = [-1] * (n + 1)
dp[1] = 0 # 0 for CY, 1 for SK
dp[2] = 1
dp[3] = 0
for i in range(4, n + 1):
    dp[i] = (dp[i-1] ^ 1) | (dp[i-3] ^ 1)
print(['CY', 'SK'][dp[-1]])
