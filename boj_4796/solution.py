t = 1
while True:
    L, P, V = map(int, input().split())
    if L == P == V == 0:
        break
    ans = V // P * L
    V %= P
    ans += min(V, L)
    print(f'Case {t}: {ans}')
    t += 1
    
