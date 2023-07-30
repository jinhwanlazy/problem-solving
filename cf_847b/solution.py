N = int(input())
xs = list(map(int, input().split()))
while True:
    xs_swap = []
    res = []
    for x in xs:
        if not res or res[-1] < x:
            res.append(x)
        else:
            xs_swap.append(x)
    print(' '.join(map(str, res)))
    xs = xs_swap
    if not xs:
        break


