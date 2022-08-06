#include <bits/stdc++.h>
using namespace std;

constexpr static int di[4] = {0, 1, 0, -1};
constexpr static int dj[4] = {1, 0, -1, 0};

vector<int> floodFill(vector<vector<int>>& grid, int src, int dst) {
  vector<int> res;
  int h = grid.size();
  int w = grid[0].size();
  for (int i = 0; i < grid.size(); ++i) {
    for (int j = 0; j < grid[0].size(); ++j) {
      if (grid[i][j] != src) {
        continue;
      }
      int count = 0;
      grid[i][j] = dst;
      queue<pair<int, int>> q;
      q.push({i, j});
      while (!q.empty()) {
        auto [i_, j_] = q.front(); q.pop();
        count++;
        for (int k = 0; k < 4; ++k) {
          int ii = i_ + di[k];
          int jj = j_ + dj[k];
          if (0 <= ii && ii < h && 0 <= jj && jj < w && grid[ii][jj] == src) {
            grid[ii][jj] = dst;
            q.push({ii, jj});
          }
        }
      }
      res.push_back(count);
    }
  }
  return res;
}

void solve() {
  int M, N, K;
  scanf("%d %d %d", &M, &N, &K);

  vector<vector<int>> grid(M, vector<int>(N, 0));
  for (int i = 0; i < K; ++i) {
    int x1, y1, x2, y2;
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
    for (int x = x1; x < x2; ++x) {
      for (int y = y1; y < y2; ++y) {
        grid[y][x] = 1;
      }
    }
  }

  auto res = floodFill(grid, 0, 2);
  printf("%ld\n", res.size());
  sort(res.begin(), res.end());
  for (int i : res) {
    printf("%d ", i);
  }
  printf("\n");
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
