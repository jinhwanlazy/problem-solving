# runtime error: max recursion exceeded
import sys
input = sys.stdin.readline
from functools import lru_cache

@lru_cache(maxsize=None)
def is_palindrome(seq, l, r):
    if l == r:
        return True
    if l + 1 == r:
        return seq[l] == seq[r]
    return is_palindrome(seq, l+1, r-1) and seq[l] == seq[r]

input()
seq = tuple(map(int, input().split()))
for __ in range(int(input())):
    l, r = map(int, input().split())
    print(1 if is_palindrome(seq, l-1, r-1) else 0)


