import sys
input = sys.stdin.readline

N, M = map(int, input().split())
G = [[] for _ in range(N)]
for _ in range(M):
    a, b = map(int, input().split())
    G[a].append(b)
    G[b].append(a)

def dfs(G, i, trace=[]):
    for j in G[i]:
        if j in trace:
            continue
        trace.append(j)
        if len(trace) == 5:
            return True
        dfs(G, j, trace)
        trace.pop()
    return False
    

for i in range(N):
    if dfs(G, i):
        print(1)
        break
else:
    print(0)
