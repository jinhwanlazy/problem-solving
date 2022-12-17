N = int(input())
a, b, c, d, e, f = xs = list(map(int, input().split()))

side = min(xs)
edge = min(
    a + b,
    a + c,
    a + d,
    a + e,

    f + b,
    f + c,
    f + d,
    f + e,

    b + c,
    c + e,
    e + d,
    d + b,
)
corner = min(
    a + b + c,
    a + c + e,
    a + e + d,
    a + d + b,
    f + b + c,
    f + c + e,
    f + e + d,
    f + d + b,
)

if N == 1:
    print(sum(xs) - max(xs))
else:
    print(4 * corner + 
          (N - 2) * 4 * edge +
          (N - 2) * (N - 2) * side +
          (N - 1) * 4 * edge +
          (N - 2) * (N - 1) * 4 * side)


