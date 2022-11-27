import sys
input = sys.stdin.readline

def solve():
    N = int(input())
    numbers = [input().strip() for _ in range(N)]
    numbers.sort()
    for i, j in zip(numbers, numbers[1:]):
        if len(j) > len(i) and i == j[:len(i)]:
            return False
    return True

for _ in range(int(input())):
    print('YES' if solve() else 'NO')
