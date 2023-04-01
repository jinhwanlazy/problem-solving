from collections import Counter
cs = Counter(input()[0] for _ in range(int(input()))).items()
res = sorted(c for c, v in cs if v >= 5)

if res:
    print(''.join(res))
else:
    print('PREDAJA')
