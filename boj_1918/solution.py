OPERATORS = {
    '*': 1,
    '/': 1,
    '+': 2,
    '-': 2,
}

class Tree:
    def __init__(self, eq):
        ops = parse(eq)
        operators = [(i, op) for i, op in enumerate(ops) if op in OPERATORS]
        if not operators:
            self.op = eq
            self.lhs = self.rhs = None
        else:
            first_op = max(operators, key=lambda x: (OPERATORS[x[1]], x[0]))
            self.op = first_op[1]
            self.lhs = Tree(''.join(ops[:first_op[0]]))
            self.rhs = Tree(''.join(ops[first_op[0]+1:]))
    
def parse(eq):
    S = []
    res = []
    for i, c in enumerate(eq):
        if c == '(':
            S.append(i)
        elif not S:
            res.append(c)
        elif c == ')':
            j = S.pop()
            if not S:
                res.append(eq[j:i+1])
    if len(res) == 1 and res[0] == eq:
        return parse(eq[1:-1])
    return res

def traverse(tree):
    if tree is None:
        return ''
    res = []
    res.append(traverse(tree.lhs))
    res.append(traverse(tree.rhs))
    res.append(tree.op)
    return ''.join(res)

eq = input()
tree = Tree(eq)
ans = traverse(tree)
print(ans)
