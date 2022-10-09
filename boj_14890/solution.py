import sys
input = sys.stdin.readline

N, L = map(int, input().split())
W = [list(map(int, input().split())) for _ in range(N)]

def valid(road):
    if all(abs(i - j) == 0 for i, j in zip(road, road[1:])):
        return True

    if any(abs(i - j) > 1 for i, j in zip(road, road[1:])):
        return False

    slope = [False] * N
    for i in range(len(road) - 1):
        j = i + 1
        if road[i] + 1 == road[j]:
            if i + 1 < L:
                return False
            if any(road[k] != road[i] for k in range(i - L + 1, j)):
                return False
            for k in range(i - L + 1, j):
                slope[k] = True

    for i in range(len(road) - 1):
        j = i + 1
        if road[i] - 1 == road[j]:
            if j + L - 1 >= N:
                return False
            if any(road[k] != road[j] for k in range(j, j + L)):
                return False
            for k in range(j, j + L):
                if slope[k]:
                    return False
                slope[k] = True
    return True
    

ans = sum(valid(row) for row in W) + sum(valid(col) for col in zip(*W))
print(ans)
