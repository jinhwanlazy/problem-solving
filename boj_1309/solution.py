N = int(input())

mod = 9901
a, b, c = 1, 1, 1
for _ in range(N-1):
    a, b, c = a + b + c, a + c, a + b
    a %= mod
    b %= mod
    c %= mod
ans = (a + b + c) % mod 
print(ans)
    
