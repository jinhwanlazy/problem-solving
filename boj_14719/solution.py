H, W = map(int, input().split())
A = [['.'] * W for _  in range(H)]
for j, h in enumerate(map(int, input().split())):
    for i in range(h):
        A[i][j] = '#'

ans = 0
for i in range(H):
    visited = [0] * W
    for j in range(W):
        if i > 0 and A[i-1][j] == '.':
            continue
        if j > 0 and A[i][j-1] == '.':
            continue
        if A[i][j] == '#' or visited[j]:
            continue
        if j == 0:
            k = 0
            while k < W and A[i][k] == '.':
                visited[k] = 1
                k += 1
            continue
        k = j
        while k < W and A[i][k] == '.':
            k += 1
        if k < W:
            for l in range(j, k):
                A[i][l] = '~'
                visited[l] = 1
                ans += 1

    # from pprint import pprint
    # for row in reversed(A):
        # print(''.join(row))
    # print()

print(ans)
