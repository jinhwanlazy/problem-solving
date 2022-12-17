import sys
input = sys.stdin.readline
W = list(input().strip())
i = 0 
while i < len(W):
    if all(j < len(W) and W[j] == 'X' for j in range(i, i + 4)):
        W[i:i+4] = list('A' * 4)
        i += 4
    elif all(j < len(W) and W[j] == 'X' for j in range(i, i + 2)):
        W[i:i+2] = list('B' * 2)
        i += 2
    elif W[i] == '.':
        i += 1
    else:
        print('-1')
        sys.exit(0)
print(''.join(W))
        
    
