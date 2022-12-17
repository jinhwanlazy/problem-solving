N, M = map(int, input().split())
count = 0
l = 1
for _ in range(int(input())):
    x = int(input())
    r = l + M
    if r <= x:
        count += x - r + 1
        l = x - M + 1
    elif x < l:
        count += l - x
        l = x
print(count)

    
