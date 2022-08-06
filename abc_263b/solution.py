N = int(input())
P = [0, 0] + list(map(int, input().split()))
D = [-1] * (N + 1)
D[1] = 0

def solve(i):
    if D[i] != -1:
        return D[i]
    D[i] = 1 + solve(P[i])
    return D[i]

ans = solve(N)
print(ans)
    

