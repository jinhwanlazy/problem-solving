N, M = map(int, input().split())

res = list(range(1, N + 1))
for _ in range(M):
    i, j = map(int, input().split())
    res[i-1:j] = reversed(res[i-1:j])
print(' '.join(map(str, res)))
