from bisect import bisect_left

M = int(input())

dp = []
dp.append(0)
dp.append(5)
dp.append(5 + 1 + 7)
for i in range(3, 10000):
    dp.append(dp[-1] + 1 + dp[-2])
    if dp[-1] > (1 << 32):
        break

def solve(M):
    if M < len('Messi Gimossi '):
        c = 'Messi Gimossi '[M]
        return c if c != ' ' else 'Messi Messi Gimossi'
    i = bisect_left(dp, M) - 1
    return solve(M-dp[i] - 1)

# for i in range(1, 30):
    # print(i, solve(i-1))

print(solve(M-1))

# print(solve(1))
