import sys
input = sys.stdin.readline
for _ in range(int(input())):
    N = int(input())
    A = input()
    B = input()
    
    w2b, b2w = 0, 0
    for i, (a, b) in enumerate(zip(A, B)):
        if a == 'W' and b == 'B':
            w2b += 1
        if a == 'B' and b == 'W':
            b2w += 1
    print(max(w2b, b2w))


    
