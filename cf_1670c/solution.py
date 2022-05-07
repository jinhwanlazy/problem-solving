import sys
input = sys.stdin.readline

def find_cycles(A, B, N):
    visited = [False] * N
    nxt = dict(zip(A, B))
    seen = set()
    cycles = []
    for a in A:
        if a in seen:
            continue
        i = a
        c = []
        while i not in seen:
            seen.add(i)
            c.append(i)
            i = nxt[i]
        cycles.append(c)
    return cycles

def count(cycle, known):
    if any(c in known for c in cycle):
        return 1
    elif len(cycle) == 1:
        return 1
    else:
        return 2

def solve():
    N = int(input())
    A = list(map(int, input().split()))
    B = list(map(int, input().split()))
    D = list(map(int, input().split()))
    
    cycles = find_cycles(A, B, N)
    known = {i for i in D if i != 0}
    # print(cycles)
    # print(known)

    ans = 1
    for c in cycles:
        ans *= count(c, known)
        ans %= 1000000007
    return ans

    # print(cycles)

for _ in range(int(input())):
    print(solve())
