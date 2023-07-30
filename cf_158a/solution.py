N, K = map(int, input().split())
A = sorted(map(int, input().split()), reverse=True)
kth = A[K-1]
ans = sum(a > 0 and a >= kth for a in A)
print(ans)

