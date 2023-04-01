A, B = input().strip().split()

min_dist = len(B)
for i in range(len(B) - len(A) + 1):
    dist = 0
    for j in range(len(A)):
        dist += A[j] != B[i + j]
    min_dist = min(min_dist, dist)

print(min_dist)
