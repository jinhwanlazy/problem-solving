import sys

s = sys.stdin.readline()
x = s.count('01') + s.count('10')
print((x + 1) // 2)
