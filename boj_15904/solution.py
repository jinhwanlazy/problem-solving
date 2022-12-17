def solve():
    s = input()
    prev = -1
    for c in 'UCPC':
        s = s[prev+1:]
        i = s.find(c)
        if i == -1:
            return False
        prev = i
    return True

print('I love UCPC' if solve() else 'I hate UCPC')
