def get_divs(n):
    divs = []
    for i in range(1, n):
        if n % i == 0:
            divs.append(i)
    return divs

while True:
    n = int(input())
    if n == -1:
        break
    divs = get_divs(n)
    if sum(divs) == n:
        print(f'{n} = {" + ".join(map(str, divs))}')
    else:
        print(f'{n} is NOT perfect.')
