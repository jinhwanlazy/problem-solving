from collections import deque
import sys
input = sys.stdin.readline

def get_field():
    field = [input().strip() for _ in range(12)]
    field = zip(*field)
    field = [deque(reversed(row)) for row in field]
    drop(field)
    return field

def drop(field):
    for i, row in enumerate(field):
        field[i] = deque(c for c in row if c != '.')
    return True


def pop(field):
    end = True
    visited = set()
    for i, row in enumerate(field):
        for j, c in enumerate(row):
            if c == '.' or (i, j) in visited:
                continue
            cnt = 0
            Q = deque()
            Q.append((i, j))
            while Q:
                i2, j2 = Q.popleft()
                for (i3, j3) in ((i2, j2 + 1), (i2, j2 - 1), (i2 + 1, j2), (i2 - 1, j2)):
                    if not(0 <= i3 < len(field) and 0 <= j3 < len(field[i3])):
                        continue
                    if (i3, j3) in visited:
                        continue
                    if field[i3][j3] != c:
                        continue
                    visited.add((i3, j3))
                    cnt += 1
                    Q.append((i3, j3))
            # print(i, j, c, cnt)
            if cnt < 4:
                continue
            end = False
            Q.append((i, j))
            while Q:
                i2, j2 = Q.popleft()
                if field[i2][j2] == '.':
                    continue
                field[i2][j2] = '.'
                for (i3, j3) in ((i2, j2 + 1), (i2, j2 - 1), (i2 + 1, j2), (i2 - 1, j2)):
                    if not(0 <= i3 < len(field) and 0 <= j3 < len(field[i3])):
                        continue
                    if field[i3][j3] == c:
                        Q.append((i3, j3))
    # from pprint import pprint
    # pprint(field)
    return not end

    

def simulate(field):
    cnt = 0
    while drop(field) and pop(field):
        cnt += 1
    return cnt

ans = simulate(get_field())
print(ans)

