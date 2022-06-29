# Input (Python 3.6+, 12.08 MB)
N = 500000

print(N, N - 1)
print('\n'.join(f'{i} {i + 1}' for i in range(1, N)))

print('\n'.join('4000' for i in range(N)))

print(1, N)
print(' '.join(f'{i}' for i in range(1, N + 1)))

# Output
2000000000
