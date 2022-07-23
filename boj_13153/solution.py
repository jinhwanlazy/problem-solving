import math

p1 = tuple(map(int, input().split()))
p2 = tuple(map(int, input().split()))
p3 = tuple(map(int, input().split()))
r = float(input())

def dist(p1, p2):
    return ((p1[0] - p2[0])**2 + (p1[1] - p2[1])**2)**0.5

a = dist(p1, p2)
b = dist(p2, p3)
c = dist(p3, p1)

A = 0.25 * math.sqrt(4 * a**2 * b**2 - (a**2 + b**2 - c**2)**2)
r2 = A / ((a + b + c) * 0.5)

print('%.3f' % ((r2 - r) / r * 100))
