def dfs(xs, vs, i):
    while True:
        if vs[i]:
            return
        vs[i] = 1
        i = xs[i]

for _ in range(int(input())):
    N = int(input())
    xs = [int(x)-1 for x in input().split()]
    vs = [0] * N
    ans = 0
    for i in range(N):
        if not vs[i]:
            dfs(xs, vs, i)
            ans += 1
    print(ans)

