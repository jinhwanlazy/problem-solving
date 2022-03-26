cache = {}
def second_to_last(n, bound):
    key = (n, bound)
    if key in cache:
        return cache[key]
    if (bound * (bound-1)) / 2 < n:
        cache[key] = 0
    elif n <= 2:
        cache[key] = 1
    else:
        cache[key] = sum(second_to_last(n-m, m) for m in range(1, min(bound, n+1)))
    #  print(bound, n, cache[key])
    return cache[key]
    
def solution(n):
    return sum(second_to_last(n-m, m) for m in range(1, n))

if __name__ == '__main__':
    print(solution(input()))
