from collections import deque

q = deque(range(1, int(input()) + 1))
ans = []
while q:
    ans.append(q.popleft())
    if q:
        q.append(q.popleft())
print(' '.join(map(str, ans)))
