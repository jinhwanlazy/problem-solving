import sys
input = sys.stdin.readline

def solve():
    B = int(input())
    rects = [list(map(int, input().split())) for _ in range(B)]
    xys = []
    for x1, y1, x2, y2 in rects:
        for x in range(x1, x2+1):
            for y in range(y1, y2+1):
                xys.append((x, y))
    xys.sort()
    x0 = sorted(x for x, _ in xys)[len(xys)//2]
    y0 = sorted(y for _, y in xys)[len(xys)//2]
    x, y = min(xys, key=lambda xy: abs(x0-xy[0])+abs(y0-xy[1]))
    # print(x0, y0, x, y)
    d = sum(abs(x - x1) + abs(y - y1) for x1, y1 in xys)
    return x, y, d
    

for t in range(int(input())):
    ans = solve()
    print(f'Case #{t+1}:', ' '.join(map(str, ans)))

