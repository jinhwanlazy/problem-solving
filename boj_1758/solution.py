import sys
input = sys.stdin.readline

N = int(input())
xs = sorted((int(input()) for _ in range(N)), reverse=True)
ans = 0
for i, x in enumerate(xs):
    ans += max(0, x - i)
print(ans)

    
