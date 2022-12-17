N = int(input())
ans = 0
for i, d in enumerate(sorted(map(int, input().split()), reverse=True)):
    ans = max(ans, i + d)
print(ans + 2)
