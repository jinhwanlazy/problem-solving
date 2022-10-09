S = input()
res = []
open_count = 0
tag = []

def rev(tag):
    res = []
    token = []
    for c in tag:
        if not token or not (token[-1].isspace() ^ c.isspace()):
            token.append(c)
        elif token:
            res.extend(list(reversed(token)))
            token = [c]
    if token:
        res.extend(list(reversed(token)))
    return res

for i, c in enumerate(S):
    if c == '<':
        open_count += 1
        if open_count == 1 and tag:
            res.extend(rev(tag))
            tag = []
    if c == '>':
        open_count -= 1
        
    if open_count > 0 or c == '>':
        res.append(c)
    else:
        tag.append(c)
if tag:
    res.extend(rev(tag))

print(''.join(res))
