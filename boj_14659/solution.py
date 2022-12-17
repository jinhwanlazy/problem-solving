import sys
input = sys.stdin.readline

stack = []
ans = 0

N = int(input())
xs = list(map(int, input().split()))
xs.append(99999999999)
for i, h in enumerate(xs):
    while stack and stack[-1][1] < h:
        j, h2 = stack.pop()
        ans = max(ans, i - j - 1)
    stack.append((i, h))
print(ans)
