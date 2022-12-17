N, M = map(int, input().split())

def solve(N, M):
    if N == 1:
        return 1
    if N <= 2:
        return min((M + 1) // 2, 4)
    if M <= 6:
        return min(M, 4)
    return M - 2
        

print(solve(N, M))


