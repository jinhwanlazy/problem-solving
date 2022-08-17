import sys
input = sys.stdin.readline

def solve(N):
    if N % 2 == 1:
        print(-1)
        return
    if N < 4:
        print(-1)
        return

    if N % 6 == 0:
        a, b = 0, N // 6
    elif N % 6 == 2:
        a = 2
        b = (N - 8) // 6
    elif N % 6 == 4:
        a = 1
        b = (N - 4) // 6
    min_fleet = a + b

    if N % 4 == 0:
        a = N // 4
        b = 0
    elif N % 4 == 2:
        a = (N - 6) // 4
        b = 1
    max_fleet = a + b
    print(min_fleet, max_fleet)
    

T = int(input())
for _ in range(T):
    N = int(input())
    solve(N)

