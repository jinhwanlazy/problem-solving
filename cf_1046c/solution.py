N, D = map(int, input().split())
S = list(map(int, input().split()))
P = list(map(int, input().split()))

x = S[D - 1] + P[0]
rank = 0
j = N - 1
for i in range(N):
    if i != D - 1:
        if S[i] + P[j] > x:
            rank += 1
        else:
            j -= 1

print(rank + 1)
