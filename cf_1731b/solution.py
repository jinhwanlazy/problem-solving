import sys
input = sys.stdin.readline
mod = int(1e9 + 7)

for _ in range(int(input())):
    N = int(input())
    ans = N * (N + 1) * (2 * N + 1) // 3 - N * (N + 1) // 2
    ans *= 2022
    ans %= mod 
    print(ans)

