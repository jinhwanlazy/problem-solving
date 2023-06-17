import sys
input = sys.stdin.readline

for _ in range(int(input())):
    l, r = [], []
    for c in input().strip():
        if c == '-':
            if l:
                l.pop()
        elif c == '<':
            if l:
                r.append(l.pop())
        elif c == '>':
            if r:
                l.append(r.pop())
        else:
            l.append(c)
    sys.stdout.write(''.join(l))
    sys.stdout.write(''.join(reversed(r)))
    sys.stdout.write('\n')
