N, K = map(int, input().split())
xs = list(map(int, input().split()))
bins = [None] * N

def next_use(i, j):
    k = i + 1
    while k < K:
        if bins[j] == xs[k]:
            return k
        k += 1
    return k


count = 0
for i, x in enumerate(xs):
    for j, b in enumerate(bins):
        if b == None or b == x:
            bins[j] = x
            break
    else:
        j = max(range(len(bins)), key=lambda j: next_use(i, j))
        bins[j] = x
        count += 1
        
        
print(count)
