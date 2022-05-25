import sys

input = sys.stdin.readline

while True:
    S = input().strip()
    if S == '.':
        break
    for i in range(1, len(S)+1):
        if len(S) % i != 0:
            continue
        substr = S[0:i]
        cnt = len(S) // i
        if all(substr == S[j*i:(j+1)*i] for j in range(1, cnt)):
            print(cnt)
            break

