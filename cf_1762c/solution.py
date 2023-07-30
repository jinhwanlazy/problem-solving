from collections import defaultdict
import sys
input = sys.stdin.readline

MOD = 998244353

def solve():
    N = int(input())
    bs = input().strip()
    memo = {((0, 1) if bs[0] == '1' else (1, 0)): 1}

    ans = 1
    for i, b in enumerate(bs[1:]):
        memo_swap = defaultdict(int)
        for (zeros, ones), cnt in memo.items():
            if b == '1':
                if zeros < ones:
                    memo_swap[(zeros + 1, ones + 1)] += cnt
                    memo_swap[(zeros + 1, ones + 1)] %= MOD
                if zeros < ones + 2:
                    memo_swap[(zeros + 0, ones + 2)] += cnt
                    memo_swap[(zeros + 0, ones + 2)] %= MOD
            else:
                if zeros > ones:
                    memo_swap[(zeros + 1, ones + 1)] += cnt
                    memo_swap[(zeros + 1, ones + 1)] %= MOD
                if zeros + 2 > ones:
                    memo_swap[(zeros + 2, ones + 0)] += cnt
                    memo_swap[(zeros + 2, ones + 0)] %= MOD
        memo = memo_swap
        print(memo)
        for k, v in memo.items():
            ans += memo[k]
            ans %= MOD
    print(ans)
                


for _ in range(int(input())):
    solve()
