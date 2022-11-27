cups = [0, 1, 0, 0]
for _ in range(int(input())):
    i, j = map(int, input().split())
    cups[i], cups[j] = cups[j], cups[i]
for i in range(1, 4):
    if cups[i]:
        print(i)
