A = input().strip()

ans = -1
for i in range(1, 8):
    for j in range(1, 8):
        for k in range(1, 8):
            if i + j + k != len(A):
                continue
            a = A[:i]
            b = A[i:i + j]
            c = A[i + j:i + j + k]
            if any(len(s) > 1 and s[0] == '0' for s in (a, b, c)):
                continue
            if any(int(s) > 1000000 for s in (a, b, c)):
                continue
            ans = max(ans, sum(map(int, (a, b, c))))
print(ans)
