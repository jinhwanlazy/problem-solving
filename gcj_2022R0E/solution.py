import sys
from dataclasses import dataclass
import random

@dataclass
class Room:
    n_passages = -1
    visit_method = None

class Action:
    pass

class Teleport(Action):
    def __init__(self, R):
        self.R = R

    def __repr__(self):
        return f'T {self.R}'

class Walk(Action):
    def __init__(self, from_R):
        self.from_R = from_R

    def __repr__(self):
        return f'W'

class Estimate(Action):
    def __init__(self, E):
        self.E = E

    def __repr__(self):
        return f'E {self.E}'

class CaveInformation:
    def __init__(self, N):
        self.N = N
        self.rooms = [None] + [Room() for _ in range(N)]
        self.non_visited = set(R for R in range(1, self.N+1))
        self.R = 0
        self.prev_action = None
        self.interaction_count = 0

    def update(self, R, P):
        self.R = R
        self.rooms[R].n_passages = P
        if isinstance(self.prev_action, Walk):
            self.rooms[R].visit_method = 'W'
        else:
            self.rooms[R].visit_method = 'T'
        if R in self.non_visited:
            self.non_visited.remove(R)
        self.interaction_count += 1

    def do_action(self):
        action = None
        if self.interaction_count % 2 == 0:
            if self.non_visited:
                action = Teleport(random.randint(1, self.N))
                # action = Teleport(random.choice(list(self.non_visited)))
        if action is None:
            action = Walk(self.R)
        self.prev_action = action
        return action

    def estimate(self):
        teleport_count = 0
        non_visited_count = 0
        mean_passages = 0
        passages_where_walkedin_room = 0
        for R in range(1, self.N+1):
            room = self.rooms[R]
            if room.visit_method == 'T':
                teleport_count += 1
                mean_passages += room.n_passages
            elif room.visit_method == 'W':
                passages_where_walkedin_room += room.n_passages
            else:
                non_visited_count += 1

        mean_passages /= (1e-8 + teleport_count) 
        est = mean_passages * (teleport_count + non_visited_count) + passages_where_walkedin_room
        return Estimate(int(est / 2))

    
def interact():
    N, K = map(int, input().split())

    cave = CaveInformation(N)
    for _ in range(K):
        R, P = map(int, input().split())
        cave.update(R, P)
        print(cave.do_action(), flush=True)

    R, P = map(int, input().split())
    cave.update(R, P)

    print(cave.estimate(), flush=True)
    

def main():
    T = int(input())
    for _ in range(T):
        interact()
    

if __name__ == '__main__':
    main()
