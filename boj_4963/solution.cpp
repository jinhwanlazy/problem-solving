#include <bits/stdc++.h>
using namespace std;

constexpr static int di[8] = {0, 0, -1, +1, -1, 1, 1, -1};
constexpr static int dj[8] = {-1, +1, 0, 0, -1, 1, -1, 1};

int floodFill(vector<vector<int>>& grid, int src, int dst) {
  int count = 0;
  int h = grid.size();
  int w = grid[0].size();
  for (int i = 0; i < grid.size(); ++i) {
    for (int j = 0; j < grid[0].size(); ++j) {
      if (grid[i][j] != src) {
        continue;
      }
      count++;
      queue<pair<int, int>> q;
      q.push({i, j});
      while (!q.empty()) {
        auto [i_, j_] = q.front(); q.pop();
        for (int k = 0; k < 8; ++k) {
          int ii = i_ + di[k];
          int jj = j_ + dj[k];
          if (0 <= ii && ii < h && 0 <= jj && jj < w && grid[ii][jj] == src) {
            grid[ii][jj] = dst;
            q.push({ii, jj});
          }
        }
      }
    }
  }
  return count;
}


int main() {
  while (true) {
    int w, h;
    scanf("%d %d", &w, &h);

    if (w == 0 && h == 0)
      return 0;

    vector<vector<int>> grid(h, vector<int>(w, 0));
    for (int i = 0; i < h; ++i) {
      for (int j = 0; j < w; ++j) {
        scanf("%d", &grid[i][j]);
      }
    }

    int ans = floodFill(grid, 1, 2);
    printf("%d\n", ans);
  }

  return 0;
}
