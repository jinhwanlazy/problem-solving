import sys
from dataclasses import dataclass
from typing import Tuple

input = sys.stdin.readline

@dataclass
class Flower:
    sm: int
    sd: int
    em: int
    ed: int

    def start(self) -> Tuple[int]:
        return (self.sm, self.sd)

    def end(self) -> Tuple[int]:
        return (self.em, self.ed)

flowers = [Flower(*map(int, input().split())) for _ in range(int(input()))]
flowers.sort(key=Flower.start, reverse=True)

t = (3, 1)
count = 0
while True:
    if not flowers:
        break
    me = None
    while flowers and flowers[-1].start() <= t:
        f = flowers.pop()
        if me is None or me < f.end():
            me = f.end()
    if me is not None:
        t = me
        count += 1
    else:
        break
    if t >= (11, 31):
        break
            
print(count if t >= (11, 31) else 0)
