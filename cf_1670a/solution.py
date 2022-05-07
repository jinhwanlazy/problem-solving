import sys
input = sys.stdin.readline

def is_sorted(A):
    for a, b in zip(A, A[1:]):
        if a > b:
            return False
    return True

for _ in range(int(input())):
    N = int(input())
    A = list(map(int, input().split()))
    
    n_neg = sum(a < 0 for a in A)

    B = [-abs(a) if i < n_neg else abs(a) for i, a in enumerate(A)]
    print('YES' if is_sorted(B) else 'NO')

