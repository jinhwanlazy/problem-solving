from math import gcd

def xGCD(a, b):
    if a < b:
        g, y, x = xGCD(b, a)
        return g, x, y
    if b == 0:
        return a, 1, 0
    g, x_, y_ = xGCD(b, a % b)
    return g, y_, x_ - (a // b) * y_


def main():
    a, b, S = map(int, input().split())
    if a == S or b == S or a + b == S:
        print('YES')
        return

    g = gcd(a, b)
    a //= g
    b //= g
    S //= g

    _, x, y = xGCD(a, b)
    x *= S
    y *= S

    if x < 0:
        k = (-x // b) + 1
        x += k * b
        y -= k * a
    if y < 0:
        k = (-y // b) + 1
        x -= k * b
        y += k * a

    # print(f'{x} * {a} + {y} * {b} => {x * a + y * b}, {S}')

    while y > 0:
        if x > 0 and y > 0 and gcd(x, y) == 1:
            print('YES')
            break
        x += b
        y -= a
    else:
        print('NO')

main()
