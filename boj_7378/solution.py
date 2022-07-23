import sys
input = sys.stdin.readline

N = int(input())
def sq_dist(x1, y1, x2, y2):
    return (x1 - x2)**2 + (y1 - y2)**2

def bingo(ps, x, y, S):
    l = min(x, S-x, y, S-y)
    return all(sq_dist(*p, x, y) <= l**2 for p in ps)

def solve():
    S, H = map(int, input().split())
    ps = [tuple(map(int, input().split())) for _ in range(H)]
    for x in range(S+1):
        for y in range(S+1):
            if any(p[0] == x and p[1] == y for p in ps):
                continue
            if  bingo(ps, x, y, S):
                print(x, y)
                return
    print('poodle')
    
for _ in range(N):
    solve()
        
