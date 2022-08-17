import sys
input = sys.stdin.readline

def count2(i):
    j = 0 
    while i % 2 != 1:
        i //= 2
        j += 1
    return j

for _ in range(int(input())):
    n = int(input())
    A = list(map(int, input().split()))
    odds = [a for a in A if a % 2 == 1]
    evens = [a for a in A if a % 2 == 0]

    if len(odds) > 0:
        print(len(evens))
        continue

    m = min(count2(i) for i in evens)
    print(m + len(evens) - 1)
    
