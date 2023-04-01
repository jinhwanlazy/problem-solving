A = [0] * 20
B = [0] * 20
A[0] = B[0] = 1

p_a = float(input()) / 100
p_b = float(input()) / 100

for _ in range(18):
    tmp = [0] * 20
    for i in range(19):
        tmp[i] += A[i] * (1.0 - p_a)
        tmp[i+1] += A[i] * p_a
    A = tmp
    
for _ in range(18):
    tmp = [0] * 20
    for i in range(19):
        tmp[i] += B[i] * (1.0 - p_b)
        tmp[i+1] += B[i] * p_b
    B = tmp

primes = {2, 3, 5, 7, 11, 13, 17, 19}

# from pprint import pprint
# pprint(A)
# pprint(B)

p_no_prime = 0
for i in range(20):
    for j in range(20):
        if i not in primes and j not in primes:
            p_no_prime += A[i] * B[j]
print(1.0 - p_no_prime)
