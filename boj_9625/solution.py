A, B = 1, 0
for _ in range(int(input())):
    A, B = B, A + B
print(A, B)
