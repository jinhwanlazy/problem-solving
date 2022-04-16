def parse_command(line):
    if line.startswith('pop'):
        return lambda lst: lst.pop() if lst else -1
    if line.startswith('size'):
        return len
    if line.startswith('empty'):
        return lambda lst: int(len(lst) == 0)
    if line.startswith('top'):
        return lambda lst: lst[-1]  if lst else -1
    if line.startswith('push'):
        return lambda lst: lst.append(int(line[5:]))

import sys
stack = []
for line in sys.stdin.read().strip().split('\n')[1:]:
    res = parse_command(line)(stack)
    if res is not None:
        print(res)
