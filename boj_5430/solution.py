from collections import deque
class MyQueue:
    def __init__(self, data):
        self.data = deque(data)
        self.forward = True

    def reverse(self):
        self.forward = not self.forward

    def delete(self):
        if self.forward:
            self.data.popleft()
        else:
            self.data.pop()

    def __repr__(self):
        if self.forward:
            return '[' + ','.join(map(str, self.data)) + ']'
        else:
            return '[' + ','.join(map(str, reversed(self.data))) + ']'

for _ in range(int(input())):
    commands = input()
    input()
    try:
        Q = MyQueue(map(int, input()[1:-1].split(',')))
    except ValueError:
        Q = MyQueue([])
    # print(Q)
    for cmd in commands:
        try:
            if cmd == 'R':
                Q.reverse()
            elif cmd == 'D':
                Q.delete()
        except Exception as e:
            print('error')
            # print(e)
            break
    else:
        print(Q)

        
