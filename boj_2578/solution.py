A = [list(map(int, input().split())) for _ in range(5)]

def get():
    for _ in range(5):
        for n in map(int, input().split()):
            yield n

def count_bingo():
    def all_zero(row):
        return not any(row)
    count = 0
    for row in A:
        if all_zero(row):
            count += 1
    for col in zip(*A):
        if all_zero(col):
            count += 1
    if all_zero(A[i][i] for i in range(5)):
        count += 1
    if all_zero(A[i][4-i] for i in range(5)):
        count += 1
    return count


def mark(n):
    for i, row in enumerate(A):
        for j, v in enumerate(row):
            if v == n:
                A[i][j] = 0
                return
        

for i, n in enumerate(get()):
    mark(n)
    # from pprint import pprint
    # pprint(A)
    if count_bingo() >= 3:
        print(i + 1)
        break
