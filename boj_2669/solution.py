grid = [[0] * 101 for _ in range(101)]
ans = 0
for _ in range(4):
    l, b, r, t = map(int, input().split())
    for x in range(l, r):
        for y in range(b, t):
            if not grid[y][x]:
                grid[y][x] = 1
                ans += 1
print(ans)
                
