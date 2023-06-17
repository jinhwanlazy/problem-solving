alpha = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
N = int(input())
equation = list(input())
variables = {c: int(input()) for c, i in zip(alpha, range(N))}
ops = {
    '+': lambda a, b: a + b,
    '-': lambda a, b: a - b,
    '*': lambda a, b: a * b,
    '/': lambda a, b: a / b,
}

stack = []
for item in equation:
    if item in variables:
        stack.append(variables[item])
    else:
        b, a = stack.pop(), stack.pop()
        stack.append(ops[item](a, b))

print('%.2f' % stack.pop())
