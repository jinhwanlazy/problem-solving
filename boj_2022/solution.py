x, y, c = map(float, input().split())
e = 1e-4

l, r = e, min(x, y)
while r - l > e:
    m = (l + r) / 2
    c_ = 1 / (1 / (x**2 - m**2)**0.5 + 1 / (y**2 - m**2)**0.5)
    if c_ < c:
        r = m
    else:
        l = m

print(m)
