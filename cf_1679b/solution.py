from collections import defaultdict
import sys
input = sys.stdin.readline

N, Q = map(int, input().split())
A = dict(enumerate(map(int, input().split())))
S = sum(A.values())

for _ in range(Q):
    query = list(map(int, input().split()))
    if query[0] == 1:
        S += query[2] - A[query[1]-1]
        A[query[1]-1] = query[2]
    else:
        i = query[1]
        A = defaultdict(lambda: i)
        S = query[1] * N
    print(S)

