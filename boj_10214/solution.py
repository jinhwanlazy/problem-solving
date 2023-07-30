for _ in range(int(input())):
    y, k = map(sum, zip(*[map(int, input().split()) for _ in range(9)]))
    if y == k:
        print('Draw')
    elif y > k:
        print('Yonsei')
    else:
        print('Korea')
