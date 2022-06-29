from functools import lru_cache
from dataclasses import dataclass

@dataclass
class Coord:
    x: int
    y: int

    def sq_dist(self, other):
        return (self.x - other.x)**2 + (self.y - other.y)**2

@dataclass
class Shark(Coord):
    size: int

@dataclass
class Prey(Shark):
    def __hash__(self):
        print(super())
        return super().super().__hash__()

@dataclass
class Status(Shark):
    age: int = 0
    exp: int = 0
    size: int = 2

    def update(self):
        self.age += 1
        self.exp += 1
        if self.exp == self.size:
            self.size += 1
            self.exp = 0
            return True
        return False

    def move_and_eat(self, other: Prey):
        self.x = other.x
        self.y = other.y
        return self.update()

N = int(input())
grid = [list(map(int, input().split())) for _ in range(N)]

preys = []
baby_shark = None

for i, row in enumerate(grid):
    for j, size in enumerate(row):
        if 0 < size <= 6:
            preys.append(Prey(j, i, size))
        elif size == 9:
            baby_shark = Status(size=2, x=j, y=i)

print(preys)
print(baby_shark)

available = []
for p in preys:
    if p.size <= baby_shark.size:
        preys.remove(p)
        available.append(p)

while available:
    closest_prey = min(available, key=baby_shark.sq_dist)
    available.remove(closest_prey)
    if baby_shark.move_and_eat(closest_prey):
        for p in preys:
            if p.size <= baby_shark.size:
                preys.remove(p)
                available.append(p)
print(baby_shark.age)
