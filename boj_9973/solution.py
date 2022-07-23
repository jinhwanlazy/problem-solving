import sys
input = sys.stdin.readline

from fractions import Fraction

pi = Fraction(3.14159)
def deg2rad(deg):
    return deg * pi / 180

for line in sys.stdin.readlines():
    if line.startswith('ENDOFINPUT'):
        break
    try:
        x, y, z = map(int, line.split())
    except:
        continue
    distance = deg2rad(min(z, 360-z)) * x
    ans = 5 * y - distance * 2
    if ans >= 0:
        res = int(ans / 5)
        print(f'YES {res}')
    else:
        res = 5 * y
        print(f'NO {res}')
