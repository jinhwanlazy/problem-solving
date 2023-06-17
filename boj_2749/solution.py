from copy import deepcopy
MOD = 1000000

class Mat2x1:
    def __init__(self, a, b):
        self.a = a
        self.b = b

class Mat2x2:
    def __init__(self, a, b, c, d):
        self.a = a
        self.b = b
        self.c = c
        self.d = d

    def __matmul__(self, other):
        if isinstance(other, Mat2x2):
            a = (self.a * other.a + self.b * other.c) % MOD
            b = (self.a * other.b + self.b * other.d) % MOD
            c = (self.c * other.a + self.d * other.c) % MOD
            d = (self.c * other.b + self.d * other.d) % MOD
            return Mat2x2(a, b, c, d)
        if isinstance(other, Mat2x1):
            a = (self.a * other.a + self.b * other.b) % MOD
            b = (self.c * other.a + self.d * other.b) % MOD
            return Mat2x1(a, b)

    def __pow__(self, n):
        res = Mat2x2(1, 0, 0, 1)
        m = self
        while n > 0:
            if n % 2:
                res = res @ m
            m = m @ m
            n //= 2
        return res

m = Mat2x2(1, 1, 1, 0)
ans = m**(int(input()) - 1)
print(ans.a)





