#include <bits/stdc++.h>
using namespace std;

enum DIR { E=1, W, N, S };

class Dice {
 public:
  vector<int> nums; // top, bottom, left, right, up, down
  int x, y;

  Dice(int x, int y) : nums(6, 0), x(x), y(y) {}

  void rotate(const vector<int>& cmd) {
    vector<int> res(6);
    for (int i = 0; i < 6; ++i) {
      res[i] = nums[cmd[i]];
    }
    nums = res;
  }

  int& top() { return nums[0]; }
  int& bottom() { return nums[1]; }
  
  void move(DIR cmd) {
    switch(cmd) {
      case DIR::E:
        rotate({2, 3, 1, 0, 4, 5});
        y++;
        break;
      case DIR::W:
        rotate({3, 2, 0, 1, 4, 5});
        y--;
        break;
      case DIR::N:
        rotate({5, 4, 2, 3, 0, 1});
        x--;
        break;
      case DIR::S:
        rotate({4, 5, 2, 3, 1, 0});
        x++;
        break;
      default:
        throw runtime_error("");
    }
  }

  bool validMove(int N, int M, DIR cmd) {
    if (y == 0 && cmd == DIR::W)
      return false;
    if (y == M-1 && cmd == DIR::E) 
      return false;
    if (x == 0 && cmd == DIR::N) 
      return false;
    if (x == N-1 && cmd == DIR::S) {
      return false;
    }
    return true;
  }
};

void solve() {
  int N, M, x, y, K;
  scanf("%d %d %d %d %d", &N, &M, &x, &y, &K);

  vector<vector<int>> grid(N, vector<int>(M));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      scanf("%d", &grid[i][j]);
    }
  }

  Dice dice(x, y);
  for (int k = 0; k < K; ++k) { 
    DIR cmd;
    scanf("%d", &cmd);
    if (!dice.validMove(N, M, cmd)) {
      continue;
    }
    dice.move(cmd);
    if (grid[dice.x][dice.y] == 0) {
      grid[dice.x][dice.y] = dice.bottom();
    }
    else {
      dice.bottom() = grid[dice.x][dice.y];
      grid[dice.x][dice.y] = 0;
    }
    printf("%d\n", dice.top());
  }
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
