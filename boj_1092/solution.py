import sys

N = int(input())
cranes = list(map(int, input().split()))
bins = [0] * N

M = int(input())
boxes = list(map(int, input().split()))
boxes.sort(reverse=True)

max_weight = max(cranes)
if any(b > max_weight for b in boxes): 
    print(-1)
    sys.exit()

for box in boxes:
    bin_idx = min((i for i in range(N) if cranes[i] >= box), key=lambda i: bins[i])
    bins[bin_idx] += 1

print(max(bins))
    
    
    
    
