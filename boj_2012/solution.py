import sys
input = sys.stdin.readline

N = int(input())
xs = sorted(int(input()) for _ in range(N))

ans = sum(abs(i + 1 - x) for i, x in enumerate(xs)) 
print(ans)
