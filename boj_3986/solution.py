ans = 0
for _ in range(int(input())):
    w = input()
    s = []
    for c in w:
        if s and s[-1] == c:
            s.pop()
        else:
            s.append(c)
    ans += not s
print(ans)

