def gen_primes(max_n=1000000):
    shieve = [1] * (max_n + 1)
    shieve[0] = shieve[1] = False
    res = []
    for i in range(2, max_n+1):
        if shieve[i]:
            res.append(i)
            for j in range(i * 2, max_n+1, i):
                shieve[j] = 0
    return res

    
primes = gen_primes()
primes_set = set(primes)

def solve(n):
    res = 0
    for i in primes:
        if i * 2 > n:
            break
        if n - i in primes_set:
            res += 1
        if i * 2 >= n:
            break
    return res
    
for _ in range(int(input())):
    n = int(input())
    print(solve(n))
        

