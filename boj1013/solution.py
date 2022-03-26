import re

def solve():
    case = input().strip()
    m = re.match(r'^(100+1+|01)+$', case)
    print('YES' if m is not None else 'NO')

def main():
    N = int(input())
    for _ in range(N):
        solve()

if __name__ == "__main__":
    main()
