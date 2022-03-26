from collections import deque

INF = 987654321
def build_graph(entrances, exits, path):
    N = len(path)+2
    src = [0] * N
    snk = [0] * N
    for ent in entrances:
        src[ent+1] = INF
    capacity = []
    capacity.append(src)
    for i, row in enumerate(path):
        row = [0] + row + [0]
        if i in exits:
            row[-1] = INF
        capacity.append(row)
    capacity.append(snk)
    
    flow = [[0] * N for _ in range(N)]
    adj = [set() for _ in range(N)]
    for i, row in enumerate(capacity):
        for j, c in enumerate(row):
            if c > 0:
                adj[i].add(j)
                adj[j].add(i)

    return capacity, flow, adj
    
def find_path(src, snk, capacity, flow, adj):
    path = {}
    q = deque()
    q.append(src)
    while q:
        u = q.popleft()
        for v in adj[u]:
            if capacity[u][v] - flow[u][v] > 0 and v not in path:
                q.append(v)
                path[v] = u
                if v == snk:
                    return path
    return None

def make_flow(src, snk, capacity, flow, path):
    c = INF
    cur = snk
    while cur != src:
        prv = path[cur]
        c = min(c, capacity[prv][cur] - flow[prv][cur])
        cur = prv
    cur = snk
    while cur != src:
        prv = path[cur]
        flow[prv][cur] += c
        flow[cur][prv] -= c
        cur = path[cur]
    return c

def solution(entrances, exits, path):
    cap, flow, adj = build_graph(entrances, exits, path)
    src, snk = 0, len(cap)-1
    max_flow = 0
    while True:
        path = find_path(src, snk, cap, flow, adj)
        if path:
            max_flow += make_flow(src, snk, cap, flow, path)
        else:
            break
    return max_flow

if __name__ == '__main__':
    print(solution(*input()))
