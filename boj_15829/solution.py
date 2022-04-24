r = 31
mod = 1234567891
d = dict(zip('abcdefghijklmnopqrstuvwxyz', range(1, 27)))

input()
print(sum(d[c] * r**i for i, c in enumerate(input())) % mod)
