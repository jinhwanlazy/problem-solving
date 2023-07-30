n = int(input())
a = list(input())
f = {str(i+1): j for i, j in enumerate(input().split())}

flag = False
for i, c in enumerate(a):
    if f[c] <= c and not flag:
        continue
    if f[c] < c and flag:
        break
    flag = True
    a[i] = f[c]

print(''.join(a))
