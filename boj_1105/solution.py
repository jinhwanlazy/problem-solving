L, R = input().strip().split()

if len(R) > len(L):
    print(0)
else:
    ans = 0
    for i, (l, r) in enumerate(zip(L, R)):
        if l == '8' and r == '8':
            ans += 1
        elif l != r:
            break
    print(ans)

        

