from collections import Counter

def sort(row):
    c = Counter(row)
    res = []
    for n in sorted(c.keys(), key=lambda n: (c[n], n)):
        if n == 0:
            continue
        res.append(n)
        res.append(c[n])
        if len(res) >= 100:
            break
    return res

def reg(rows):
    max_len = max(len(row) for row in rows)
    for row in rows:
        if len(row) < max_len:
            row.extend([0] * (max_len - len(row)))
    return rows
        
def R(M):
    M = [sort(row) for row in M]
    M = reg(M)
    return M

def C(M):
    M = [sort(col) for col in zip(*M)]
    M = reg(M)
    return list(zip(*M))

def step(M):
    n_rows = len(M)
    n_cols = len(M[0])
    if n_rows >= n_cols:
        return R(M)
    else:
        return C(M)

r, c, k = map(int, input().split())
M = [list(map(int, input().split())) for _ in range(3)]

for t in range(101):
    if r <= len(M) and c <= len(M[0]) and M[r-1][c-1] == k:
        print(t)
        break
    M = step(M)
else:
    print(-1)
