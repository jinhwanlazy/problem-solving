import sys

res = []
for _ in range(int(sys.stdin.readline())):
    res.append(str(sum(map(int, sys.stdin.readline().split()))))
print('\n'.join(res))
