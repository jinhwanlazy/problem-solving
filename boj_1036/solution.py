charset = '0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ'
c2i = {c: i for i, c in enumerate(charset)}
i2c = charset
base = 36

def w2i(word):
    return sum(base**i * c2i[c] for i, c in enumerate(reversed(word)))

def i2w(i):
    res = []
    while (i > 0):
        res.append(i2c[i % base])
        i //= base
    return ''.join(reversed(res))
    
    
if __name__ == "__main__":
    N = int(input())
    words = [input() for _ in range(N)]
    K = int(input())

    weights = {i: 0 for i in range(base)}
    for word in words:
        for i, c in enumerate(reversed(word)):
            weights[c2i[c]] += base**i * (base - 1 - c2i[c])

    ans = 0
    idxs = sorted(range(base), key=weights.__getitem__, reverse=True)
    for word in words:
        for idx, _ in zip(idxs, range(K)):
            word = word.replace(i2c[idx], 'Z')
        ans += w2i(word)

    if ans == 0:
        print(0)
    else:
        print(i2w(ans))
