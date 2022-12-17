n = int(input())
if n in [1, 3]:
    print(-1)
elif (n % 5) % 2 == 0:
    print(n // 5 + (n % 5) // 2)
else:
    print(n // 5 - 1 + (n % 5 + 5) // 2)
    
