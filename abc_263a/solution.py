a, b, c, d, e = sorted(map(int, input().split()))
ans = a == b == c and d == e
ans |= a == b and c == d == e
print('Yes' if ans else 'No')
