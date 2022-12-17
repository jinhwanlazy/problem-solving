from collections import deque

def solve():
    S = input().strip()
    T = deque(input().strip())

    inv = False
    while len(S) < len(T):
        if not inv:
            inv ^= T[-1] == 'B'
            T.pop()
        else:
            inv ^= T[0] == 'B'
            T.popleft()
    if inv:
        T = ''.join(reversed(T))
    else:
        T = ''.join(T)
    if S == T:
        return 1
    return 0

print(solve())

        
    
