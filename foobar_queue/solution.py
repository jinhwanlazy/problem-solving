def solution(start, length):
    res = 0
    for l in range(length):
        i = start + length * l
        res ^= xor_range(i, i+length-l-1)
    return res


def xor_range(n, m):
    if n == 0:
        res = 0
        m_mod4 = m % 4
        if m_mod4 == 0:
            res = m
        elif m_mod4 == 1:
            res = 1
        elif m_mod4 == 2:
            res = m+1
        elif m_mod4 == 3:
            res = 0
        return res
    else:
        return xor_range(0, n-1) ^ xor_range(0, m)
    return res2
        
if __name__ == '__main__':
    print(solution(*input()))
