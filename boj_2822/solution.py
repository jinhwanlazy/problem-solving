xs = [int(input()) for _ in range(8)]
ys = sorted(range(8), key=xs.__getitem__, reverse=True)[:5]
print(sum(xs[i] for i in ys))
print(' '.join(map(lambda i: str(i + 1), sorted(ys))))
