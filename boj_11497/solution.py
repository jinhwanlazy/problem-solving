for _ in range(int(input())):
    N = int(input())
    A = sorted(map(int, input().split()))
    ans = max(b - a for a, b in zip(A, A[2:]))
    print(ans)
