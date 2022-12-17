N, L = map(int, input().split())
hs = sorted(map(int, input().split()))

for h in hs:
    if h <= L:
        L += 1
    else:
        break
print(L)

