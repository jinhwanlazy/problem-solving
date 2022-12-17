N = int(input())
K = int(input())
sensors = sorted(set(map(int, input().split())))

diffs = [j - i for i, j in zip(sensors, sensors[1:])]
if K == 1:
    print(sum(diffs))
else:
    diffs.sort()
    ans = sum(diffs[:-(K-1)])
    print(ans)


N, K = map(int, input().split())
sensors = sorted(set(map(int, input().split())))

diffs = [j - i for i, j in zip(sensors, sensors[1:])]
if K == 1:
    print(sum(diffs))
else:
    diffs.sort()
    ans = sum(diffs[:-(K-1)])
    print(ans)

