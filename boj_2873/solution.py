R, C = map(int, input().split())
W = [list(map(int, input().split())) for _ in range(R)]

ans = []
while R > 3:
    ans.append('R' * (C-1))
    ans.append('D')
    ans.append('L' * (C-1))
    ans.append('D')
    R -= 2
while C > 3:
    ans.append('D' * (R-1))
    ans.append('R')
    ans.append('U' * (R-1))
    ans.append('R')
    C -= 2
if R == 3:
    ans.append('R' * (C-1))
    ans.append('D')
    ans.append('L' * (C-1))
    ans.append('D')
    ans.append('R' * (C-1))
elif C == 3:
    ans.append('D' * (R-1))
    ans.append('R')
    ans.append('U' * (R-1))
    ans.append('R')
    ans.append('D' * (R-1))
elif W[-1][-2] < W[-2][-1]:
    ans.append('RD')
else:
    ans.append('DR')
print(''.join(ans))

    
    

