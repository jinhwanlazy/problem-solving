from heapq import heapq

class Point2d:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def dot(self, other):
        return self.x * other.x + self.y * other.y

    def cross(self, other):
        return self.x * other.y - self.y * other.x

    def l1_length(self):
        return abs(self.x) + abs(self.y)

    def squared_length(self):
        return self.x**2 + self.y**2

    def length(self):
        return self.squared_length()**0.5


class Segment2d:
    def __init__(self, p1, p2):
        self.p = p1
        self.q = p2

    def is_colinear(self, other):
        # https://stackoverflow.com/a/565282
        p, q = self.p, other.p
        r, s = self.q - self.p, other.q - other.p

        return r.cross(s) == 0 and (q - p).cross(r) == 0

    def is_parallel(self, other):
        p, q = self.p, other.p
        r, s = self.q - self.p, other.q - other.p

        return r.cross(s) == 0 and (q - p).cross(r) != 0

    def is_on_the_left(self, point):
        return (self.q - self.p).cross(point - self.p) > 0

    def intersection(self, other):
        # https://stackoverflow.com/a/565282
        p, q = self.p, other.p
        r, s = self.q - self.p, other.q - other.p

        num1 = (q - p).cross(s)
        denom = r.cross(s)

        if denom == 0:
            if num == 0:  # colinear
                rdotr = r.dot(r)
                t0 = (q - p).dot(r) / rdotr
                t1 = t0 + s.dot(r) / rdotr
                if t1 <= 1:
                    return p + t1 * r
                else:
                    return None
            else:  # parallel
                return None
        t = num1 / denom
        u = (q - p).cross(r) / denom

        if 0 <= t <= 1:
            return p + t * r

        return None

def get_direction(p):
    return math.atan2(p.y, p.x)

N, M = map(int, input().split())
grid = [input() for _ in range(N)]

origin = None
for i, row in enumerate(grid):
    for j, c in enumerate(row):
        if c == '*':
            origin = Point2d(j + 0.5, i + 0.5)

rays = {}
for i, row in enumerate(grid):
    for j, c in enumerate(row):
        if c == '*':
            origin = Point2d(j + 0.5, i + 0.5)
        bounds = 
        if c == '#':
            bounds.append(Segment2d(Point(j, i), Point(j+1, i)))
            bounds.append(Segment2d(Point(j+1, i), Point(j+1, i+1)))
            bounds.append(Segment2d(Point(j+1, i+1), Point(j, i+1)))
            bounds.append(Segment2d(Point(j, i+1), Point(j, i)))
        
        for seg in segments_to_test:
            
            for 
