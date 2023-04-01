template = '''0000    1 2222 3333 4  4 5555 6666 7777 8888 9999
0  0    1    2    3 4  4 5    6       7 8  8 9  9
0  0    1 2222 3333 4444 5555 6666    7 8888 9999
0  0    1 2       3    4    5 6  6    7 8  8    9
0000    1 2222 3333    4 5555 6666    7 8888    9 '''

def draw(i):
    l = 5 * i
    res = []
    for r in range(5):
        res.append(template[50 * r + l:50 * r + l + 4].rstrip())
    return '\n'.join(res)

res = []
for c in input():
    res.append(draw(int(c)))
print('\n\n'.join(res))

