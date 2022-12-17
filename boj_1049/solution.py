N, M = map(int, input().split())
sixs, ones = zip(*(map(int, input().split()) for _ in range(M)))
six = min(sixs)
one = min(ones)

ans = N // 6 * six + min(six, (N % 6) * one)
ans = min(ans, N * one)
print(ans)
