import sys
from heapq import *
input = sys.stdin.readline

K = int(input())
W, H = map(int, input().split())
grid = [list(map(int, input().split())) for _ in range(H)]

def solve():
    if (H, W) == (1, 1):
        return 0
    visited = set()
    Q = [(0, K, 0, 0)]

    def visit(cnt, r, c, k, use_k, diffs):
        for dr, dc in diffs:
            r2, c2 = r + dr, c + dc
            k2 = k if not use_k else k-1
            if not (0 <= r2 < H and 0 <= c2 < W) or grid[r2][c2] == 1:
                continue
            if (k2, r2, c2) in visited:
                continue
            if (r2, c2) == (H - 1, W - 1):
                return cnt + 1
            visited.add((k2, r2, c2))
            heappush(Q, (cnt + 1, k2, r2, c2))
        return -1
            
    while Q:
        cnt, k, r, c = heappop(Q)
        ans = visit(cnt, r, c, k, False, 
                              ((1, 0), (-1, 0), (0, 1), (0, -1)))
        if ans >= 0:
            return ans
        if k > 0:
            ans = visit(cnt, r, c, k, True, 
                  ((1, -2), (1, 2), (-1, -2), (-1, 2), (2, 1), (2, -1), (-2, 1), (-2, -1)))
            if ans >= 0:
                return ans
    return -1

print(solve())
