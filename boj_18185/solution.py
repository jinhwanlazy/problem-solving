N = int(input())
A = list(map(int, input().split()))

# dp[i][0:3] := i 번째 까지의 최적의 1, 2, 3 라면 묶음의 갯수.
dp = [[0] * 3 for _ in range(N)]
dp[0][0] = A[0]
for i in range(1, N):
    a = A[i]

    pairs = min(dp[i-1][0], a)
    a -= pairs
    dp[i-1][0] -= pairs
    dp[i][1] += pairs

    triplets = min(dp[i-1][1], a)
    a -= triplets
    dp[i-1][1] -= triplets
    dp[i][2] += triplets
    
    dp[i][0] += a

ans = sum(a * 3 + b * 5 + c * 7 for a, b, c in dp)
print(ans)
