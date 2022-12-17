for _ in range(int(input())):
    C = int(input())
    ans = []
    for u in [25, 10, 5, 1]:
        ans.append(C // u)
        C %= u
    print(' '.join(map(str, ans)))
