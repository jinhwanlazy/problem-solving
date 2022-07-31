'''
Distract the Trainers
=====================

The time for the mass escape has come, and you need to distract the bunny trainers so that the workers can make it out! Unfortunately for you, they're watching the bunnies closely. Fortunately, this means they haven't realized yet that the space station is about to explode due to the destruction of the LAMBCHOP doomsday device. Also fortunately, all that time you spent working as first a minion and then a henchman means that you know the trainers are fond of bananas. And gambling. And thumb wrestling.

The bunny trainers, being bored, readily accept your suggestion to play the Banana Games.

You will set up simultaneous thumb wrestling matches. In each match, two trainers will pair off to thumb wrestle. The trainer with fewer bananas will bet all their bananas, and the other trainer will match the bet. The winner will receive all of the bet bananas. You don't pair off trainers with the same number of bananas (you will see why, shortly). You know enough trainer psychology to know that the one who has more bananas always gets over-confident and loses. Once a match begins, the pair of trainers will continue to thumb wrestle and exchange bananas, until both of them have the same number of bananas. Once that happens, both of them will lose interest and go back to supervising the bunny workers, and you don't want THAT to happen!

For example, if the two trainers that were paired started with 3 and 5 bananas, after the first round of thumb wrestling they will have 6 and 2 (the one with 3 bananas wins and gets 3 bananas from the loser). After the second round, they will have 4 and 4 (the one with 6 bananas loses 2 bananas). At that point they stop and get back to training bunnies.

How is all this useful to distract the bunny trainers? Notice that if the trainers had started with 1 and 4 bananas, then they keep thumb wrestling! 1, 4 -> 2, 3 -> 4, 1 -> 3, 2 -> 1, 4 and so on.

Now your plan is clear. You must pair up the trainers in such a way that the maximum number of trainers go into an infinite thumb wrestling loop!

Write a function solution(banana_list) which, given a list of positive integers depicting the amount of bananas the each trainer starts with, returns the fewest possible number of bunny trainers that will be left to watch the workers. Element i of the list will be the number of bananas that trainer i (counting from 0) starts with.

The number of trainers will be at least 1 and not more than 100, and the number of bananas each trainer starts with will be a positive integer no more than 1073741823 (i.e. 2^30 -1). Some of them stockpile a LOT of bananas.

Languages
=========

To provide a Python solution, edit solution.py
To provide a Java solution, edit Solution.java

Test cases
==========
Your code should pass the following test cases.
Note that it may also be run against hidden test cases not shown here.

-- Python cases --
Input:
    solution.solution(1,1)
Output:
    2

Input:
    solution.solution([1, 7, 3, 21, 13, 19])
Output:
    0

-- Java cases --
Input:
    solution.solution(1,1)
Output:
    2

Input:
    Solution.solution([1, 7, 3, 21, 13, 19])
Output:
    0
'''

class BipartiteMatching:
    def __init__(self, graph, n_dst):
        self.graph = graph
        self.n_dst = n_dst
        self.matches = [-1] * n_dst

    def solve(self):
        res = 0
        for src, dsts in enumerate(self.graph):
            visited = [False] * self.n_dst
            res += self._dfs(src, visited)
        return res

    def _dfs(self, src, visited): 
        for dst in self.graph[src]:
            if visited[dst]:
                continue
            visited[dst] = True
            if (self.matches[dst] == -1 
                    or self._dfs(self.matches[dst], visited)):
                self.matches[dst] = src
                return True
        return False


def dead_lock(a, b):
    while True:
        if a == b:
            return False
        if (a + b) & 1 == 1:
            return True
        if a & 1 == 0 and b & 1 == 0:
            a, b = a / 2, b / 2
            continue
        if a > b:
            a, b = b, a
        a, b = a * 2, b - a
    

def solution(banana_list):
    N = len(banana_list)
    graph = [[] for _ in range(N)]

    for i in range(N-1):
        for j in range(i+1, N):
            if dead_lock(banana_list[i], banana_list[j]):
                graph[i].append(j)
                graph[j].append(i)

    # Not sure why BipartiteMatching works here. 
    # Shouldn't we use Blossom algorithm?
    bm = BipartiteMatching(graph, N)
    ans = N - 2 * (bm.solve() / 2)
    return ans

if __name__ == '__main__':
    print(solution(input()))


