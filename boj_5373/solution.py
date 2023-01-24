import sys
input = sys.stdin.readline

from dataclasses import dataclass
from typing import List

@dataclass
class Vec3:
    x: int
    y: int
    z: int

    def dot(self, other) -> int:
        return self.x * other.x + self.y * other.y + self.z * other.z

    def __eq__(self, other) -> bool:
        return self.x == other.x and self.y == other.y and self.z == other.z


@dataclass
class Mat3:
    data: List[int]

    def __init__(self, data=[]):
        if not data:
            data = [1, 0, 0, 0, 1, 0, 0, 0, 1]
        self.data = data

    def __matmul__(self, other):
        if isinstance(other, Vec3):
            return Vec3(*(self.data[3*i+0] * other.x + 
                          self.data[3*i+1] * other.y + 
                          self.data[3*i+2] * other.z for i in range(3)))
        if isinstance(other, Mat3):
            return Mat3([sum(self.data[3*i+k] * other.data[3*k+j] for k in range(3)) for
                         i in range(3) for j in range(3)])
        print(other)
        raise

    def __add__(self, other):
        if isinstance(other, Mat3):
            return Mat3([self.data[i] + other.data[i] for i in range(9)])
        raise

    def t(self):
        return Mat3([self.data[3*j+i] for i in range(3) for j in range(3)])

    @classmethod
    def I(cls):
        return cls()

    @classmethod
    def from_vec(cls, v, reverse):
        c = cls([0, -v.z, v.y, v.z, 0, -v.x, -v.y, v.x, 0])
        rot = cls.I() + c + c @ c
        if reverse:
            rot = rot.t()
        return rot


DIRECTIONS = {
    'L': Vec3(-1, 0, 0),
    'R': Vec3(1, 0, 0),
    'F': Vec3(0, -1, 0),
    'B': Vec3(0, 1, 0),
    'D': Vec3(0, 0, -1),
    'U': Vec3(0, 0, 1),
}

INITIAL_COLORS = {
    'L': 'g',
    'R': 'b',
    'F': 'r',
    'B': 'o',
    'D': 'y',
    'U': 'w',
}

@dataclass
class Square:
    direction: Vec3
    color: str

    def __init__(self, direction):
        self.direction = DIRECTIONS[direction]
        self.color = INITIAL_COLORS[direction]

@dataclass
class Block:
    position: Vec3
    squares: List[Square]

    def __init__(self, position, directions):
        self.position = position
        self.squares = [Square(direction) for direction in directions]

    def rotate(self, direction, reverse):
        if self.position.dot(direction) == 1:
            r = Mat3.from_vec(direction, reverse)
            self.position = r @ self.position
            for s in self.squares:
                s.direction = r @ s.direction

class RubiksCube:
    """ block index
     0--------1--------2
    /|       /|       /|
   3--------+--------4 |
  /| |     /  |     /| |
 5--------6--------7 | |
 | | 8----|---+----|-|-9
 | |/|    |   /    | |/|
 | +------|--+-----|-+ |
 |/| |    |/       |/| |
10--------+-------11 | |
 | |12----|---13---|-|-14
 | |/     |   /    | |/
 |15------|-+------|-16
 |/       |/       |/
17-------18-------19
"""
    def __init__(self):
        self.blocks = [
            Block(Vec3(-1, 1, 1), 'ULB'),
            Block(Vec3(0, 1, 1), 'UB'),
            Block(Vec3(1, 1, 1), 'URB'),
            Block(Vec3(-1, 0, 1), 'UL'),
            Block(Vec3(1, 0, 1), 'UR'),
            Block(Vec3(-1, -1, 1), 'ULF'),
            Block(Vec3(0, -1, 1), 'UF'),
            Block(Vec3(1, -1, 1), 'URF'),

            Block(Vec3(-1, 1, 0), 'LB'),
            Block(Vec3(1, 1, 0), 'RB'),
            Block(Vec3(-1, -1, 0), 'LF'),
            Block(Vec3(1, -1, 0), 'RF'),

            Block(Vec3(-1, 1, -1), 'DLB'),
            Block(Vec3(0, 1, -1), 'DB'),
            Block(Vec3(1, 1, -1), 'DRB'),
            Block(Vec3(-1, 0, -1), 'DL'),
            Block(Vec3(1, 0, -1), 'DR'),
            Block(Vec3(-1, -1, -1), 'DLF'),
            Block(Vec3(0, -1, -1), 'DF'),
            Block(Vec3(1, -1, -1), 'DRF'),
        ]

    def rotate(self, cmd):
        direction = DIRECTIONS[cmd[0]]
        reverse = cmd[1] == '+'
        for block in self.blocks:
            block.rotate(direction, reverse)


    def get_color(self, position, direction):
        for block in self.blocks:
            # print(position, direction, block.position)
            if block.position == position:
                for square in block.squares:
                    if square.direction == direction:
                        return square.color
        raise
                    
    def print_up(self):
        u = DIRECTIONS['U']
        res = [
            self.get_color(Vec3(-1, 1, 1), u),
            self.get_color(Vec3(0, 1, 1), u),
            self.get_color(Vec3(1, 1, 1), u),
            self.get_color(Vec3(-1, 0, 1), u),
            'w',
            self.get_color(Vec3(1, 0, 1), u),
            self.get_color(Vec3(-1, -1, 1), u),
            self.get_color(Vec3(0, -1, 1), u),
            self.get_color(Vec3(1, -1, 1), u),
        ]
        print('{0}{1}{2}\n{3}{4}{5}\n{6}{7}{8}'.format(*res))

for _ in range(int(input())):
    N = int(input())
    cube = RubiksCube()
    for cmd in input().split():
        cmd = cmd.strip()
        cube.rotate(cmd)
    cube.print_up()

