from fractions import Fraction
sqrt2 = Fraction(
        '1.41421356237309504880168872420969807856967187537694807317667'
        '9737990732478462107038850387534327641572735013846230912297024'
        '9248360558507372126441214970999358314132226659275055927557999'
        '5050115278206057147010955997160597027453459686201472851741864')

def solve_brute_force(n):
    return int(sum(int((2*(i**2))**0.5) for i in range(1, n+1)))

def solve_recursive(n):
    if n < 1:
        return 0
    if n == 1:
        return 1
    m = int((sqrt2 - 1) * n)
    return n*m + n*(n+1)/2 - m*(m+1)/2 - solve_recursive(m)

def solution(s):
    ans = solve_recursive(int(s))
    return str(ans)

