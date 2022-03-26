def solve(x, y):
    if x == y == 1:
        return 0
    if x == y:
        return None
    if x > y:
        x, y = y, x
    n = y / (x+1)
    return solve(y-x*n, x) + n

def solution(x, y):
    try:
        return str(solve(int(x), int(y)))
    except TypeError:
        return 'impossible'

if __name__ == '__main__':
    print(solution(*input()))
