ps = map(int, input().split())
x, y, r = map(int, input().split())

p = min(enumerate(ps), key=lambda ip: abs(x - ip[1]))
if p[1] == x:
    print(p[0] + 1)
else:
    print(0)

