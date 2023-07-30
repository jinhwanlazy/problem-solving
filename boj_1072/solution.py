import math
X, Y = map(int, input().split())
p = Y * 100 // X
if p >= 99:
    print(-1)
else:
    q = p + 1
    N = math.ceil((q * X - 100 * Y) / (100 - q))
    print(N)
