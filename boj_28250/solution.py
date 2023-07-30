from collections import Counter

N = int(input())
A = Counter(map(int, input().split()))

ans = 0
ans += A[0] * A[1] * 2
ans += A[0] * (N - A[1] - A[0])
ans += A[0] * (A[0] - 1) // 2
print(ans)

