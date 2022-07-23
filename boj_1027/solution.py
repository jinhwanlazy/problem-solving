N = int(input())
hs = list(map(int, input().split()))

def visible(i, j):
    a = (hs[j] - hs[i]) / (j - i)
    b = hs[i] - a * i
    for k in range(i+1, j):
        hk = a * k + b
        if hs[k] >= hk:
            return False
    return True
        

vs = [0] * N
for i in range(N-1):
    for j in range(i+1, N):
        if visible(i, j):
            vs[i] += 1
            vs[j] += 1

print(max(vs))

