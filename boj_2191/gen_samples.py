from random import randint
N, M, S, V = 2, 2, randint(1, 100), randint(1, 100)
print(N, M, S, V)
for _ in range(N + M):
    x, y = randint(0, 1000000), randint(0, 1000000)
    print(f'{x/1000:.3f} {y/1000:.3f}')

