import itertools
import sys

for line in sys.stdin.readlines():
    if line.strip() == '0':
        break
    nums = list(map(int, line.split()))
    for combi in itertools.combinations(nums[1:], 6):
        print(' '.join(map(str, combi)))
    print()
    
    

    
