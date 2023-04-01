N, K = map(int, input().split())

m = K * (K + 1) // 2
if N < m:
    print(-1)
elif (N - m) % K == 0:
    print(K - 1)
else:
    print(K)
    
