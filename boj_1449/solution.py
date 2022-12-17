N, L = map(int, input().split())
holes = sorted(map(int, input().split()))

count = 0
while holes:
    r = holes[-1]
    while holes and holes[-1] > r - L:
        holes.pop()
    count += 1
print(count)
    

