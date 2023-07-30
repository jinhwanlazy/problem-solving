N, M = map(int, input().split())

A = list(range(1, N + 1))

for _ in range(M):
    i, j, k = map(lambda x: int(x) - 1, input().split())
    A[i:j+1] = A[k:j+1] + A[i:k]

print(' '.join(map(str, A)))
    
