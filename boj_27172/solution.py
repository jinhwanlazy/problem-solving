import sys
input = sys.stdin.readline

N = int(input())
C = list(map(int, input().split()))
MAX = 1000001

cards = [0] * MAX
for i in C:
    cards[i] = 1

scores = [0] * MAX

for i in range(1, MAX):
    if cards[i]:
        for j in range(2 * i, MAX, i):
            if cards[j]:
                scores[i] += 1
                scores[j] -= 1

print(' '.join([str(scores[i]) for i in C]))
        
