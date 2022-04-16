class Queue:
    def __init__(self):
        self.data_ = {}
        self.head_ = 0
        self.tail_ = 0

    def push(self, x):
        self.data_[self.tail_] = x
        self.tail_ += 1

    def pop(self):
        if self.empty():
            return -1
        res = self.data_.pop(self.head_)
        self.head_ += 1
        return res;

    def size(self):
        return self.tail_ - self.head_

    def empty(self):
        return int(self.size() == 0)

    def front(self):
        if self.empty():
            return -1
        return self.data_[self.head_]

    def back(self):
        if self.empty():
            return -1
        return self.data_[self.tail_-1]

import sys
queue = Queue()
res = []
for cmd in sys.stdin.read().strip().split('\n')[1:]:
    if cmd.startswith('push'):
        queue.push(cmd.split()[-1])
    elif cmd.startswith('pop'):
        res.append(queue.pop())
    elif cmd.startswith('size'):
        res.append(queue.size())
    elif cmd.startswith('empty'):
        res.append(queue.empty())
    elif cmd.startswith('front'):
        res.append(queue.front())
    elif cmd.startswith('back'):
        res.append(queue.back())
sys.stdout.write('\n'.join(map(str, res)))

