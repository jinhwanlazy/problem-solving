import sys
input = sys.stdin.readline

def solve():
    N = int(input())
    P = input()
    S = set(input().split()[1:])

    specials = []
    for i, c in enumerate(P):
        if c in S:
            specials.append(i)

    lifes = []
    for i in range(len(specials)):
        if len(lifes) == 0:
            lifes.append(specials[i])
        else:
            lifes.append(max(lifes[-1], specials[i] - specials[i-1]))
    if not lifes:
        return 0
    else:
        return lifes[-1]

            
for _ in range(int(input())):
    print(solve())
