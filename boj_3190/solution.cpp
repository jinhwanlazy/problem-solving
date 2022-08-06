#include <bits/stdc++.h>
using namespace std;

constexpr static int di[4] = {0, 1, 0, -1};
constexpr static int dj[4] = {1, 0, -1, 0};

using Coord = pair<int, int>;

class Snake {
 public:
  int N;

  deque<Coord> body = {};
  set<Coord> occupied = {};
  int dir = 0;

  Snake(int N) : N(N)  {
    body.push_front({1, 1});
    occupied.insert({1, 1});
  }
  
  bool stretch() {
    const Coord& prv = body.front();
    Coord nxt(prv.first + di[dir], prv.second + dj[dir]);
    if (nxt.first < 1 || nxt.first > N)
      return false;
    if (nxt.second < 1 || nxt.second > N)
      return false;
    if (occupied.find(nxt) != occupied.end()) {
      return false;
    }
    
    body.push_front(nxt);
    occupied.insert(nxt);
    return true;
  }

  void shrink() {
    occupied.erase(body.back());
    body.pop_back();
  }
  
  Coord head() const {
    return body.front();
  }
};

void solve() {
  int N;
  scanf("%d", &N);

  int K;
  scanf("%d", &K);

  set<Coord> apples;
  for (int k = 0; k < K; ++k) {
    int i, j;
    scanf("%d %d", &i, &j);
    apples.insert({i, j});
  }

  int L;
  scanf("%d", &L);
  
  deque<pair<int, int>> commands;
  for (int k = 0; k < L; ++k) {
    int i;
    char c;
    scanf("%d %c", &i, &c);
    commands.push_back({i, c});
  }

  Snake snake(N);
  for (int t = 1;; t++) {
    
    if (!snake.stretch()) {
      printf("%d\n", t);
      break;
    }

    if (apples.find(snake.head()) != apples.end()) {
      apples.erase(snake.head());
    }
    else {
      snake.shrink();
    }
    
    if (t == commands.front().first) {
      auto [_, c] = commands.front();
      commands.pop_front();
      if (c == 'D' )
        snake.dir = snake.dir == 3 ? 0 : snake.dir + 1;
      else 
        snake.dir = snake.dir == 0 ? 3 : snake.dir - 1;
    }
  }
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
