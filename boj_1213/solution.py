import sys
    
offset = ord('A')
counter = [0] * 26
for c in input():
    counter[ord(c) - offset] += 1

left = []
center = ''
for i in range(26):
    left.append(chr(i+offset) * (counter[i] // 2))
    if counter[i] % 2 == 1:
        if center:
            print("I'm Sorry Hansoo ")
            sys.exit()
        else:
            center = chr(i+offset)
            counter[i] = 0

ans = []
ans.extend(left)
ans.append(center)
ans.extend(reversed(left))
ans = ''.join(ans)
print(ans)
