import sys
input = sys.stdin.readline

N, M, K = map(int, input().split())
A = [list(map(int, input().split())) for _ in range(N)]

field = [[5] * N for _ in range(N)]
trees = {}
for _ in range(M):
    x, y, z = map(int, input().split())
    trees.setdefault((x-1, y-1), []).append(z)

for zs in trees.values():
    zs.sort()

def step_spring_and_summer():
    for x, y in trees.keys():
        zs = trees[(x, y)]
        zs_swap = []
        deads = 0
        for z in zs:
            if field[x][y] >= z:
                zs_swap.append(z + 1)
                field[x][y] -= z
            else:
                deads += z // 2
        field[x][y] += deads
        trees[(x, y)] = zs_swap

dxdys = ((-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1))

def step_fall():
    new_trees = {}
    for x, y in trees.keys():
        zs = trees[(x, y)]
        for z in zs:
            if z % 5 != 0:
                continue
            for dx, dy in dxdys:
                if dx == 0 and dy == 0:
                    continue
                x2 = x + dx
                y2 = y + dy
                if not (0 <= x2 < N and 0 <= y2 < N):
                    continue
                new_trees.setdefault((x2, y2), []).append(1)
    for key, zs in new_trees.items():
        trees.setdefault(key, []).extend(zs)
    for zs in trees.values():
        zs.sort()

def step_winter():
    for i in range(N):
        field_i = field[i]
        A_i = A[i]
        for j in range(N):
            field_i[j] += A_i[j]

for _ in range(K):
    step_spring_and_summer()
    step_fall()
    step_winter()


ans = sum(len(zs) for zs in trees.values())
print(ans)



