import sys
input = sys.stdin.readline

N = int(input())
scores = [int(input()) for _ in range(N)]

count = 0
for i in range(N-1, 0, -1):
    j = i - 1;
    count += max(0, scores[j] - scores[i] + 1)
    scores[j] = min(scores[j], scores[i] - 1)
print(count)
