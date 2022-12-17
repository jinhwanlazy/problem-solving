N = int(input())

count = 0;
couple_count = 0
left_ok = True
for i, c in enumerate(input()):
    if c == 'S':
        if left_ok:
            left_ok = True
            count += 1
        else:
            left_ok = False
            count += 1
    elif couple_count % 2 == 0:
        if left_ok:
            count += 1
            left_ok = False
        else:
            left_ok = False
        couple_count += 1
    else:
        if left_ok:
            raise
        else:
            left_ok = False
            count += 1
        couple_count += 1

print(count)
            
        
            

