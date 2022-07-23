import random

w, h, x1, y1, x2, y2 = map(int, input().split())

def ccw(x1, y1, x2, y2, x3, y3):
    res = (y2 - y1) * (x3 - x2) - (x2 - x1) * (y3 - y2)
    if res == 0:
        return 0
    return 1 if res > 0 else -1

def rand_point():
    a = (random.randrange(w+1), random.choice((0, h)))
    b = (random.choice((0, w)), random.randrange(h+1))
    return random.choice((a, b))


while True:
    p1, p2 = rand_point(), rand_point()
    if p1 != p2 and ccw(*p1, *p2, x1, y1) * ccw(*p1, *p2, x2, y2) == -1:
        print(*p1, *p2)
        break

