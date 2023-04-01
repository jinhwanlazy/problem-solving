N = int(input())
src = list(map(int, input()))
dst = list(map(int, input()))

tests = []
for _ in range(4):
    tests.append(src.copy())

tests[1][0] ^= 1
tests[1][1] ^= 1
tests[2][0] ^= 1
tests[2][1] ^= 1
tests[2][-1] ^= 1
tests[2][-2] ^= 1
tests[3][-1] ^= 1
tests[3][-2] ^= 1

for t, test in enumerate(tests):
    count = [0, 1, 2, 1][t]
    for i in range(N - 2):
        if test[i] != dst[i]:
            test[i] ^= 1
            test[i+1] ^= 1
            test[i+2] ^= 1
            count += 1
    if test[-3:] == dst[-3:]:
        print(count)
        break
else:
    print(-1)
