s = []
for c in input().strip():
    s.append(c)
    if len(s) >= 4 and s[-4:] == ['P', 'P', 'A', 'P']:
        s.pop()
        s.pop()
        s.pop()
        s.pop()
        s.append('P')
if s == ['P']:
    print('PPAP')
else:
    print('NP')
