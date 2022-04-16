from collections import deque

N, K = map(int, input().split())
q = deque(range(1, N+1))
seq = []
while q:
    q.rotate(-K+1)
    seq.append(q.popleft())

print(f"<{', '.join(map(str, seq))}>")
