def solve(xs, W):
    coords = [(0, 0), (0, 1), (0, 2), (1, 2), (2, 2), (2, 1), (2, 0), (1, 0)]
    if xs == [8]:
        return all(W[i][j] == 'O' for i, j in coords)
    if len(xs) == 0:
        return all(W[i][j] == 'X' for i, j in coords)

    for i in range(8):
        j, k = coords[i]
        if W[j][k] == 'X':
            break
    res = [0]
    for j in range(8):
        k, l = coords[(i + j) % 8]
        if W[k][l] == 'X':
            if res[-1] != 0:
                res.append(0)
        else:
            res[-1] += 1
    if res[-1] == 0:
        res.pop()
    res.sort()
    return res == xs
        
        
for _ in range(int(input())):
    W = [input() for _ in range(3)]
    xs = list(map(int, input().split()))[1:]
    print(int(solve(xs, W)))
        
