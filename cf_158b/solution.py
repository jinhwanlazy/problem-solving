from collections import Counter

N = int(input())
counter = Counter(map(int, input().split()))

ans = 0
ans += counter[4]
ans += counter[3]
counter[1] = max(0, counter[1] - counter[3])
ans += (counter[2] + 1) // 2
counter[2] = counter[2] % 2
counter[1] = max(0, counter[1] - counter[2] * 2)
ans += (counter[1] + 3) // 4
print(ans)
