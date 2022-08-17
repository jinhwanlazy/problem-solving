import sys
input = sys.stdin.readline

for _ in range(int(input())):
    n, k = map(int, input().split())
    A = list(map(int, input().split()))

    if k < n:
        s = 0
        cnt = 0
        ans = 0
        for i, a in enumerate(A):
            cnt += 1
            s += a
            if cnt == k:
                ans = max(ans, s)
                cnt -= 1
                s -= A[i-k]
        ans += k * (k-1) // 2
        print(ans)
        continue
    
    ans = sum(A)
    ans += k * (k-1) // 2 - (k - n) * (k - n + 1) // 2 + (k - n)
    print(ans)

