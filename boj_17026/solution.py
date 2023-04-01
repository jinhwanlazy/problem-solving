from operator import itemgetter
import sys

input = sys.stdin.readline

ps = (map(int, input().split()) for _ in range(int(input())))
ps = sorted(((y - x, y + x) for x, y in ps), key=itemgetter(0), reverse=True)

ans = 0
max_y = 0
prev_x = None
for x, y in ps:
    if y > max_y:
        ans += prev_x is None or x < prev_x
        max_y = y
    prev_x = x

print(ans)

