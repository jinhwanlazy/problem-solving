N, B, C = map(int, input().split())
A = list(map(int, input().split()))

ans = 0
prv = [A[0], 0, 0]
for i in range(1, N):
    nxt = [A[i], 0, 0]

    if C <= B:
        pairs = min(prv[0], nxt[0])
        prv[0] -= pairs
        nxt[0] -= pairs
        nxt[1] += pairs

        triplets = min(prv[1], nxt[0])
        prv[1] -= triplets
        nxt[0] -= triplets
        nxt[2] += triplets

    ans += prv[0] * B
    ans += prv[1] * (B + C)
    ans += prv[2] * (B + 2 * C)
    prv = nxt

ans += prv[0] * B
ans += prv[1] * (B + C)
ans += prv[2] * (B + 2 * C)

print(ans)
