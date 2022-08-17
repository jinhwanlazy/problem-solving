import sys 
input = sys.stdin.readline

for _ in range(int(input())):
    x = int(input())
    bits = []
    for i in range(31):
        if ((x >> i) & 1) == 1:
            bits.append(i)
    y = (1 << bits[0])
    if len(bits) == 1:
        for i in range(31):
            if ((x >> i) & 1) == 0:
                y += 1 << i
                break
    print(y)
