import sys
input = sys.stdin.readline

N = int(input())
S = list(map(int, input().split()))

def op1(i):
    for i in range(i, N+1, i):
        S[i-1] ^= 1

def op2(i):
    j = 0
    while 1 <= i - j - 1 and i + j + 1 <= N and S[i - j - 2] == S[i + j]:
        j += 1
    for k in range(i - j - 1, i + j):
        S[k] ^= 1
        

for _ in range(int(input())):
    sex, i = map(int, input().split())
    [None, op1, op2][sex](i)

for i in range(0, N, 20):
    print(' '.join(map(str, S[i:i+20])))


