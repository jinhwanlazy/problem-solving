N = int(input())
i = 0
ans = 0
for j in map(int, input().split()):
    if i == j:
        ans += 1
        i = (i + 1) % 3
print(ans)
    
