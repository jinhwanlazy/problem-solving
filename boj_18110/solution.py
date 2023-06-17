import sys
input = sys.stdin.readline

xs = [int(input()) for _ in range(int(input()))]
xs.sort()

def round(x, div):
    half_div = div // 2 if div % 2 == 0 else div // 2 + 1
    if (x % div) < half_div:
        return x // div
    else:
        return x // div + 1

def score(xs):
    if not xs:
        return 0
    n = len(xs)
    l = round(3 * n, 20)
    r = n - l
    s = round(sum(xs[l:r]), (r - l))
    return s

print(score(xs))


