def verify(pegs, r):
    if r <= 1:
        return False
    for peg1, peg2 in zip(pegs, pegs[1:]):
        r = peg2 - peg1 - r
        if r < 1:
            return False
    return True

def compute_r(pegs):
    numerator = 0
    for i, peg in enumerate(pegs):
        sign = -1 if i % 2 == 0 else 1
        mult = 2 if i == 0 or i == len(pegs)-1 else 4
        numerator += sign * mult * peg
    denominator = 3 if len(pegs) % 2 == 0 else 1
    if numerator % denominator == 0:
        return numerator / denominator, 1
    else:
        return numerator, denominator
    
def solution(pegs):
    n, d = compute_r(pegs)
    r = float(n) / float(d)
    if verify(pegs, r):
        return [n, d]
    else:
        return [-1, -1]

if __name__ == '__main__':
    print(solution(input()))
