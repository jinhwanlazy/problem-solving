from collections import deque

N, K = map(int, input().split())
Q = deque(range(1, N+1))
ans = []
while Q:
    for _ in range(K-1):
        Q.append(Q.popleft())
    ans.append(Q.popleft())
print('<%s>' % ', '.join(map(str, ans)))
