import sys
input = sys.stdin.readline

def opposite(closing):
    return {
        ')': '(',
        ']': '[',
    }[closing]

def value(closing):
    return {
        ')': 2,
        ']': 3,
    }[closing]

def is_opening(c):
    return c in '(['

def is_bracket(c):
    return isinstance(c, str) and c in '([])'

def solve():
    stack = []
    for c in input().strip():
        if not is_bracket(c):
            return 0
        if is_opening(c):
            stack.append(c)
            continue
        o = opposite(c)
        if not stack:
            return 0
        x = 0
        while stack and stack[-1] != o:
            if not isinstance(stack[-1], int):
                return 0
            x += stack.pop()
        if not stack or stack[-1] != o:
            return 0
        stack.pop()
        stack.append(value(c) * (1 if x == 0 else x))
    if any(is_bracket(c) for c in stack):
        return 0
    return sum(stack)

print(solve())
