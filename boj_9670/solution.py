import sys
from dataclasses import dataclass
from functools import partial
from operator import attrgetter
from fractions import Fraction


@dataclass
class Device:
    name: str
    price: int
    height: Fraction
    width: Fraction

    @property
    def area(self): 
        return self.width * self.height


devices = [
    Device('iPad Mini', 319, Fraction(1024), Fraction(768)),
    Device('Galaxy Tab', 419, Fraction(1024), Fraction(600)),
    Device('iPhone 4S', 450, Fraction(960), Fraction(640)),
    Device('iPad4', 519, Fraction(2048), Fraction(1536)),
    Device('iPhone 5C', 599, Fraction(1136), Fraction(640)),
    Device('Galaxy Tab2', 600, Fraction(1280), Fraction(800)),
    Device('Galaxy S4', 630, Fraction(1080), Fraction(1920)),
    Device('iPhone 5S', 719, Fraction(1136), Fraction(640)),
]
devices.sort(key=attrgetter('price'))

def use_ratio(dev, H, W):
    def use_ratio_(H, W):
        scale = min(dev.height / H, dev.width / W)
        H, W = int(H * scale), int(W * scale)
        return H * W / dev.area
    return max(use_ratio_(H, W), use_ratio_(W, H))


for line in sys.stdin.readlines():
    H, W = map(Fraction, line.split())
    if H == W == 0:
        break
    dev = max(devices, key=partial(use_ratio, H=H, W=W))
    print(dev.price)




