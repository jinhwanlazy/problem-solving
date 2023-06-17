def ys(x):
    return 10 * (x // 30 + 1)

def ms(x):
    return 15 * (x // 60 + 1)

N = int(input())
xs = list(map(int, input().split()))
y_sum = sum(map(ys, xs))
m_sum = sum(map(ms, xs))
if y_sum < m_sum:
    print('Y', y_sum)
elif y_sum == m_sum:
    print('Y M', y_sum)
else:
    print('M', m_sum)
