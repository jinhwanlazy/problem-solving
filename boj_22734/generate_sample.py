import numpy as np

N = 10
max_coord = 100

ps = np.random.uniform(0, max_coord, (N, 2));
# ps = np.random.randint(0, max_coord, (N, 2)).astype(float)

rs = np.zeros((N, 1))
for i in range(N):
    p = ps[i]
    others = np.concatenate((ps[:i], ps[i+1:]))
    dist = np.linalg.norm(others - p[None], axis=1)
    rs[i, 0] = int(np.random.uniform(0, dist.min() / 2))

data = np.concatenate((rs, ps), axis=1)

ans = np.Inf
for i in range(N-1):
    for j in range(i+1, N):
        dist = (ps[i] - ps[j]).__pow__(2).sum().__pow__(0.5) - rs[i, 0] - rs[j, 0]
        ans = min(ans, dist)

# print(N)
# for r, x, y in data:
    # print(r, x, y)
# print(0)

with open('./sample_generated.in', 'w') as f:
    f.write(str(N))
    f.write('\n')
    for r, x, y in data:
        f.write(' '.join(map(str, (r, x, y))))
        f.write('\n')
    f.write('0')


# print('ans: ', ans)
with open('./sample_generated.out', 'w') as f:
    f.write(str(ans))
