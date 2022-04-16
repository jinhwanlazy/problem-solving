def gen_A(N):
    return list(range(1, N+1))

def solution(A, B):
    target_sum = (sum(A) + sum(B)) 
    A = sorted(A)
    B = sorted(B, reverse=True)
    
    
T = int(input())
for case in range(1, T+1):
    N = int(input())
    A = gen_A(N)
    print(' '.join(map(str, A)), flush=True)
    B = list(map(int, input().split()))
    C = solution(A, B)
    print(' '.join(map(str, solution(A, B))), flush=True)
    
N = int(in)
