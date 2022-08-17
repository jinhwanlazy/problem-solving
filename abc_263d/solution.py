N, L, R = map(int, input().split())
A = [0] + list(map(int, input().split())) + [0]

dpL = [0] * (N + 2)
for i in range(1, N+1):
    dpL[i] = min(dpL[i-1] + A[i], L * i)

dpR = [0] * (N + 2)
for i in range(N, 0, -1):
    dpR[i] = min(dpR[i+1] + A[i], R * (N-i+1))

ans = min(l + r for l, r in zip(dpL, dpR[1:]))
print(ans)
