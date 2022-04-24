def count2_in_fact(N):
    res = 0
    while N > 0:
        N //= 2
        res += N
    return res

def count5_in_fact(N):
    res = 0
    while N > 0:
        N //= 5
        res += N
    return res

N, K = map(int, input().split())
count_5 = count5_in_fact(N) - count5_in_fact(K) - count5_in_fact(N-K)
count_2 = count2_in_fact(N) - count2_in_fact(K) - count2_in_fact(N-K)
print(min(count_5, count_2))
    
