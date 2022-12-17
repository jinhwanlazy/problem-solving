for _ in range(int(input())):
    N = int(input())
    xs = list(map(int, input().split()))
    
    ans = 0
    max_val = xs[-1]
    while xs:
        x = xs.pop()
        ans += max(0, max_val - x)
        max_val = max(max_val, x)
    print(ans)
