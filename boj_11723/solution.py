import sys

data = 0
for i, line in enumerate(sys.stdin):
    if i == 0:
        continue
    cmd, *i = line.split()
    if i:
        i = int(i[0])
    if cmd == 'add':
        data |= 1 << i
    elif cmd == 'check':
        sys.stdout.write(f'{(data >> i) & 1}\n')
    elif cmd == 'remove':
        data &= ~(1 << i)
    elif cmd == 'toggle':
        data ^= (1 << i)
    elif cmd == 'all':
        data = (1 << 21) - 1
    elif cmd == 'empty':
        data = 0
    else:
        raise

