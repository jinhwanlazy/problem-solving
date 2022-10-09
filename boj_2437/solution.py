N = int(input())
ws = sorted(map(int, input().split()))
x = 0 
for w in ws:
    # 현재 [0, x] 내의 모든 수를 측정가능
    # 이때 w <= x + 1 이라면 [x + 1, w + x] 내의 무게가 추가적으로 측정 가능해짐
    # 아니라면 x + 1 은 측정 불가.
    if w > x + 1:
        break
    x += w
print(x + 1)
