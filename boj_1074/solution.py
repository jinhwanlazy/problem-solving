def Z(n, r, c):
    if n == 0:
        return 0
    div = 2 ** (n-1)
    m = div**2 * (c // div + (r // div) * 2)
    return m + Z(n-1, r % div, c % div)

print(Z(*map(int, input().split())))
