class Octree:
    def __init__(self, max_depth, xmin, xmax, ymin, ymax, zmin, zmax):
        self.xmin = xmin
        self.xmax = xmax
        self.ymin = ymin
        self.ymax = ymax
        self.zmin = zmin
        self.zmax = zmax
        self.children = [None] * 8
        self.points = None
        self.count = 0
        self.depth = max_depth

        if self.depth > 0:
            self.children = [None] * 8
        else:
            self.points = []

    @property
    def xmid(self):
        return (self.xmin + self.xmax) // 2

    @property
    def ymid(self):
        return (self.ymin + self.ymax) // 2

    @property
    def zmid(self):
        return (self.zmin + self.zmax) // 2

    @property
    def corner_points(self):
        for z in (self.zmin, self.zmax):
            for y in (self.ymin, self.ymax):
                for x in (self.xmin, self.xmax):
                    yield x, y, z

    def gen_child(self, idx):
        xmid = self.xmid
        ymid = self.ymid
        zmid = self.zmid
        return [
            lambda: Octree(self.depth-1, xmin, xmid, ymin, ymid, zmin, zmid),
            lambda: Octree(self.depth-1, xmid+1, xmax, ymin, ymid, zmin, zmid),
            lambda: Octree(self.depth-1, xmin, xmid, ymid+1, ymax, zmin, zmid),
            lambda: Octree(self.depth-1, xmid+1, xmax, ymid+1, ymax, zmin, zmid),
            lambda: Octree(self.depth-1, xmin, xmid, ymin, ymid, zmid+1, zmax),
            lambda: Octree(self.depth-1, xmid+1, xmax, ymin, ymid, zmid+1, zmax),
            lambda: Octree(self.depth-1, xmin, xmid, ymid+1, ymax, zmid+1, zmax),
            lambda: Octree(self.depth-1, xmid+1, xmax, ymid+1, ymax, zmid+1, zmax)
        ][idx]()

    def closest_corner(self, x, y, z):
        return min(self.corner_points, key=lambda p: self.sq_dist(x, y, z, *p))

    def farthest_corner(self, x, y, z):
        return max(self.corner_points, key=lambda p: self.sq_dist(x, y, z, *p))

    def insert(self, x, y, z):
        self.count += 1
        if self.depth > 0: 
            cid = int(x > self.xmid) + (int(y > self.ymid) << 1) + (int(z > self.zmid) << 2)
            if self.children[cid] is None:
                self.children[cid] = self.gen_child(cid)
            self.children[cid].insert(x, y, z)
        else:
            self.points.append((x, y, z))
        
    def query(self, x, y, z, r):
        if self.count == 0:
            return 0
        if not self.contains(x, y, z):
            if self.sq_dist(x, y, z, *self.closest_corner(x, y, z)) > r * r:
                return 0
        if self.sq_dist(x, y, z, *self.farthest_corner(x, y, z)) <= r * r:
            return self.count
        if self.depth == 0:
            return sum(self.sq_dist(x, y, z, *p) <= r * r for p in self.points)
        else:
            return sum(c.query(x, y, z, r) for c in self.children if c is not None)

    def contains(self, x, y, z):
        return self.xmin <= x <= self.xmax and self.ymin <= y <= self.ymax and self.zmin <= z <= self.zmax

    @staticmethod
    def sq_dist(x1, y1, z1, x2, y2, z2):
        return (x1 - x2)**2 + (y1 - y2)**2 + (z1 - z2)**2

    def __repr__(self):
        lines = []
        lines.append(f'Octree(d={self.depth}, bound=({self.xmin}, {self.xmax}, {self.ymin}, {self.ymax}, {self.zmin}, {self.zmax}), cnt={self.count}')
        if self.depth > 0:
            for child in self.children:
                c_line = str(child)
                c_line = '--' + c_line.replace('\n', '\n--')
                lines.append(c_line)
        return '\n'.join(lines) + ')'

def brute_force(points, x, y, z, r):
    def dist(x1, y1, z1, x2, y2, z2):
        return (x1 - x2)**2 + (y1 - y2)**2 + (z1 - z2)**2
    r2 = r * r
    return sum(dist(*p, x, y, z) <= r2 for p in points)

import sys
input = sys.stdin.readline

points = []
xmin, xmax = 987654321, 0
ymin, ymax = 987654321, 0
zmin, zmax = 987654321, 0
for _ in range(int(input())):
    x, y, z = map(int, input().split())
    points.append((x, y, z))
    xmin, xmax = min(xmin, x), max(xmax, x)
    ymin, ymax = min(ymin, y), max(ymax, y)
    zmin, zmax = min(zmin, z), max(zmax, z)

# for _ in range(int(input())):
    # x, y, z, r = map(int, input().split())
    # print(brute_force(points, x, y, z, r))

octree = Octree(4, xmin, xmax, ymin, ymax, zmin, zmax)

for p in points:
    octree.insert(*p)

for _ in range(int(input())):
    x, y, z, r = map(int, input().split())
    ans = octree.query(x, y, z, r)
    print(ans)


