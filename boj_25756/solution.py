N = int(input())
A = list(map(int, input().split()))

def step(v, a):
    return 1 - (1 - v) * (1 - a)

v = 0
for a in A:
    v = step(v, a / 100)
    print(v * 100)

