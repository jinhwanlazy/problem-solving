def solve():
    l1, b1, r1, t1, l2, b2, r2, t2 = map(int, input().split())
    if r2 < l1 or r1 < l2 or t1 < b2 or t2 < b1:
        return 'd'
    if (r1 == l2 or r2 == l1) and (b1 == t2 or b2 == t1):
        return 'c'
    if (r1 == l2 or r2 == l1) or (b1 == t2 or b2 == t1):
        return 'b'
    return 'a'

for _ in range(4):
    print(solve())
