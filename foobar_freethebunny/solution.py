import itertools as it

def solution(num_buns, num_required):
    perm = list(it.combinations(range(num_buns), num_buns-num_required+1))
    res = []
    for i in range(num_buns):
        res.append([j for j, p in enumerate(perm) if i in p])
    return res

if __name__ == '__main__':
    print(solution(*input()))
