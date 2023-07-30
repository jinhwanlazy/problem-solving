from collections import Counter
import sys
input = sys.stdin.readline

def solve():
    N = int(input())
    s = input().strip()
    counter = Counter(s)
    if counter['('] != counter[')']:
        return -1

    stack = []
    start = None
    ans = {}
    for i, c in enumerate(s):
        if not stack:
            stack.append(c)
            start = c
        else:
            if stack[-1] == c:
                stack.append(c)
            else:
                stack.pop()
        ans.setdefault(start, []).append(i)
    if stack:
        return -1

    print(len(ans))
    cnt = 0
    res = [''] * N
    for key, inds in ans.items():
        cnt += 1
        for i in inds:
            res[i] = cnt
    return ' '.join(map(str, res))
        

for _ in range(int(input())):
    print(solve())
