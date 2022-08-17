#include <bits/stdc++.h>
using namespace std;

enum MoveResult { Good = 0, Fail, Finish, Stuck };

constexpr static int di[4] = {0, 1, 0, -1};
constexpr static int dj[4] = {1, 0, -1, 0};


struct Coord { 
  int i;
  int j;
  
  Coord& operator+=(const Coord& rhs) {
    i += rhs.i;
    j += rhs.j;
    return *this;
  }

  bool operator==(const Coord& rhs) const {
    return i == rhs.i && j == rhs.j;
  }
};

Coord operator+(const Coord& lhs, const Coord& rhs) {
  return {lhs.i + rhs.i, lhs.j + rhs.j};
}

static const Coord dirs[4] = {
  Coord{0, 1},
  Coord{1, 0},
  Coord{0, -1},
  Coord{-1, 0},
};

const Coord OUT{-1, -1};

struct State{
  vector<vector<char>> grid;

  int depth = 0;
  Coord red;
  Coord blue;

  State(int H, int W) : grid(H, vector<char>(W, '.')) {}

  MoveResult move(const Coord& direction) {
    Coord blueBak = blue;
    Coord redBak = red;
    bool done = false;
    while (!done) {
      done = true;
      Coord tmp = blue + direction;
      if (valid(tmp) && tmp != red) {
        switch (grid[tmp.i][tmp.j]) {
          case 'O': blue = OUT; done = false; break;
          case '.': blue = tmp; done = false; break;
          case '#': break;
          default: throw runtime_error("You cannot reach here!");
        }
      }
      tmp = red + direction;
      if (valid(tmp) && tmp != blue) {
        switch (grid[tmp.i][tmp.j]) {
          case 'O': red = OUT; done = false; break;
          case '.': red = tmp; done = false; break;
          case '#': break;
          default: throw runtime_error("You cannot reach here!");
        }
      }
      if (red == redBak && blue == blueBak) {
        return MoveResult::Stuck;
      }
    }
    if (!valid(blue)) {
      return MoveResult::Fail;
    }
    if (!valid(red)) {
      return MoveResult::Finish;
    }
    return MoveResult::Good;
  }

  bool valid(const Coord& c) {
    return 0 <= c.i && c.i < grid.size() && 0 <= c.j && c.j < grid[0].size();
  }
};

void solve() {
  int N, M;
  scanf("%d %d", &N, &M);


  State s(N, M);
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      char c;
      scanf(" %c", &c);
      if (c == 'R') s.red = {i, j};
      else if (c == 'B') s.blue = {i, j};
      else s.grid[i][j] = c;
    }
  }

  queue<State> Q;
  Q.push(s);
  
  while (!Q.empty()) {
    State s = Q.front();
    Q.pop();

    //printf("(%d %d) (%d %d) %d\n", s.blue.i, s.blue.j, s.red.i, s.red.j, s.depth);
  
    for (const Coord& direction : dirs) {
      State ss = s;
      ss.depth += 1;
      auto res = ss.move(direction);
      switch (res) {
        case MoveResult::Finish: 
          printf("%d\n", ss.depth);
          return;
        case MoveResult::Good:
          if (ss.depth < 10) {
            Q.push(ss);
          }
          break;
        case MoveResult::Fail:
          break;
        case MoveResult::Stuck:
          break;
        default:
          throw runtime_error("You cannot reach here!");
      }
    }
  }
  printf("%d\n", -1);
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
