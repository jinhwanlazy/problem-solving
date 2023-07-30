N = int(input())
prices = list(map(int, input().split()))
dp = [0] * (N + 1)
for i in range(1, N + 1):
    dp[i] = min(dp[i - j - 1] + p for j, p in enumerate(prices) if i - j - 1 >= 0)
print(dp[N])
