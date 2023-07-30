n_max = 100001
mod = 1_000_000_009
dp1 = [0] * n_max
dp1[1] = 1
dp1[2] = 0
dp1[3] = 1

dp2 = [0] * n_max 
dp2[1] = 0
dp2[2] = 1
dp2[3] = 1

dp3 = [0] * n_max
dp3[1] = 0
dp3[2] = 0
dp3[3] = 1

for i in range(4, n_max):
    dp1[i] = (dp2[i-1] + dp3[i-1]) % mod
    dp2[i] = (dp1[i-2] + dp3[i-2]) % mod
    dp3[i] = (dp1[i-3] + dp2[i-3]) % mod

for _ in range(int(input())):
    n = int(input())
    print((dp1[n] + dp2[n] + dp3[n]) % mod)

    

