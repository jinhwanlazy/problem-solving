import random

N = 100000
M = 100000

print(N)
for _ in range(N):
    x = random.randint(0, 1000000)
    y = random.randint(0, 1000000)
    z = random.randint(0, 1000000)
    print(x, y, z)

print(M)
for _ in range(M):
    x = random.randint(0, 1000000)
    y = random.randint(0, 1000000)
    z = random.randint(0, 1000000)
    r = random.randint(1, 1000000)
    print(x, y, z, r)




