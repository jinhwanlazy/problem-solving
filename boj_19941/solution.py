N, K = map(int, input().split())
HP = input()

ans = 0
h = 0
for i, p in enumerate(HP):
    if p != 'P':
        continue
    while h < N and (HP[h] != 'H' or h < i - K):
        h += 1
    if h == N:
        break;
    if i - K <= h <= i + K:
        h += 1
        ans += 1

print(ans)
