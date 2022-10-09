from collections import defaultdict
import sys
input = sys.stdin.readline

N = int(input())
words = [input().strip() for _ in range(N)]
chars = set(''.join(words))
digits = (9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

scores = defaultdict(int)
for word in words:
    for i, c in enumerate(reversed(word)):
        scores[c] += 10**i

chars = sorted(chars, key=scores.__getitem__, reverse=True)
ans = sum(scores[c] * d for c, d, in zip(chars, digits))
print(ans)
