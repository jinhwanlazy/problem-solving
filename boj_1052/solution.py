N, K = map(int, input().split())

def reduce(bins):
    for i in range(31):
        bins[i+1] += bins[i] // 2
        bins[i] %= 2

bins = [0] * 32
bins[0] = N
reduce(bins)

ans = 0
while sum(bins) > K:
    i = min(i for i in range(30) if bins[i] > 0)
    ans += 2**i
    bins[i] += 1
    reduce(bins)

print(ans)
