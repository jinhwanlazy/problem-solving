import sys
input = sys.stdin.readline

N, game = input().split()
N = int(N)
game = {
    'Y': 2,
    'F': 3,
    'O': 4,
}[game]

others = {input() for _ in range(N)}
print((len(others)) // (game - 1))
