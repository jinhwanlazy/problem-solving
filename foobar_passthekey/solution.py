from collections import deque
import itertools

def solution(l):
    def divisible_by_3(l):
        return sum(l) % 3 == 0

    for n in range(len(l), 0, -1):
        res = 0
        for combi in itertools.combinations(l, n):
            if divisible_by_3(combi):
                res = max(res, 
                        int(''.join(map(str, sorted(combi, reverse=True)))))
        if res > 0:
            return res
    return 0

if __name__ == '__main__':
    print(solution(input()))
