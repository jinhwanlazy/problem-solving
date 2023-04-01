N, M = map(int, input().split())

bins = list(range(N + 1))

for _ in range(M):
    i, j = map(int, input().split())
    bins[i], bins[j] = bins[j], bins[i]

print(' '.join(map(str, bins[1:])))


