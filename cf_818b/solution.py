n, m = map(int, input().split())
ls = list(map(int, input().split()))
ls = [l - 1 for l in ls]
res = [-1] * n
l0 = ls[0]

for l1, l2 in zip(ls, ls[1:]):
    a = (l2 - l1) % m
    if res[l1] != -1 and res[l1] != a:
        print(-1)
        break
    res[l1] = a
print(res)
