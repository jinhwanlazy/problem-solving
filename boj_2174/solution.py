from dataclasses import dataclass
import sys
input = sys.stdin.readline

DIRS = [
    [1, 0],  # E
    [0, -1], # S
    [-1, 0], # W
    [0, 1],  # N
]

C2DIR = {
    'E': 0,
    'S': 1,
    'W': 2,
    'N': 3,
}

A, B = map(int, input().split())
N, M = map(int, input().split())

@dataclass
class Robot:
    idx: int
    direction: int
    x: int
    y: int

    def rot_r(self):
        self.direction = (self.direction + 1) % 4
        
    def rot_l(self):
        self.direction = (self.direction + 3) % 4


robots = []
grid = [[None] * A for _ in range(B)]

for i in range(N):
    x, y, c = input().split()
    x = int(x)-1
    y = int(y)-1
    robots.append(Robot(i + 1, C2DIR[c], x, y))
    grid[y][x] = robots[-1]

def run():
    for i in range(M):
        i, command, n = input().split()
        i = int(i) - 1
        n = int(n)
        for _ in range(n):
            if command == 'R':
                robots[i].rot_r()
            elif command == 'L':
                robots[i].rot_l()
            elif command == 'F':
                r = robots[i]
                x, y = r.x, r.y
                dx, dy = DIRS[r.direction]
                x2, y2 = x + dx, y + dy
                if not (0 <= x2 < A and 0 <= y2 < B):
                    print(f'Robot {r.idx} crashes into the wall')
                    return False
                if grid[y2][x2] is not None:
                    print(f'Robot {r.idx} crashes into robot {grid[y2][x2].idx}')
                    return False
                grid[y2][x2] = r
                grid[y][x] = None
                r.x, r.y = x2, y2
    return True
        
if run():
    print('OK')
