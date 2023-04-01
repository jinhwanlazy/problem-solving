from bisect import bisect
import sys
input = sys.stdin.readline

fibs = [0, 1]
while fibs[-1] < 1e10:
    fibs.append(sum(fibs[-2:]))

for _ in range(int(input())):
    n = int(input())
    
    ans = []
    while n > 0:
        i = bisect(fibs, n) - 1
        ans.append(fibs[i])
        n -= fibs[i]

    print(' '.join(map(str, sorted(ans))))

