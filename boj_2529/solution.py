N = int(input())
xs = input().split()

res0, res1 = None, None

def dfs(seq):
    global res0, res1
    if len(seq) == N + 1:
        if not res0:
            res0 = seq[:]
        res1 = seq[:]
        return
    
    for i in '0123456789':
        if i in seq:
            continue
        if seq and xs[len(seq)-1] == '>' and seq[-1] < i:
            continue
        if seq and xs[len(seq)-1] == '<' and seq[-1] > i:
            continue
        seq.append(i)
        dfs(seq)
        seq.pop()

dfs([])
print(''.join(res1))
print(''.join(res0))
