cs = input()
n = len(cs)
dp = [0] * (len(cs) + 1)
if cs[0] == '0':
    print(0)
else:
    dp[0] = dp[1] = 1
    for i in range(2, n + 1):
        if cs[i-1] != '0':
            dp[i] += dp[i-1]
        if cs[i-2] != '0' and 1 <= int(cs[i-2:i]) <= 26:
            dp[i] += dp[i-2]
        dp[i] %= 1000000
    print(dp[-1])
