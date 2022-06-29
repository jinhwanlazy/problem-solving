import sys
MOD = 1000000007

def mul(A, B):
    C = [[sum(A[i][j] * B[j][k] for j in range(len(B))) % MOD for k in range(len(B[0]))] for i in range(len(A))]
    return C

def pow(A, B):
    if B == -1:
        return [[0]]
    if B == 0:
        return [[1]]
    if B == 1:
        return [[x % MOD for x in row] for row in A]
    
    res = pow(A, B // 2)
    res = mul(res, res)
    if B % 2 == 1:
        res = mul(res, A)
    return res

A = [[1, 1], [1, 0]]
C = pow(A, int(input()) - 1)
print(C[0][0])
