import math

def solution(area):
    res = []
    while area >= 1:
        cur = int(math.floor(area**0.5)**2)
        area -= cur
        res.append(cur)
    return res

if __name__ == '__main__':
    print(solution(input()))
