#include <bits/stdc++.h>
using namespace std;

constexpr static int di[4] = {0, 0, -1, +1};
constexpr static int dj[4] = {-1, +1, 0, 0};

int floodFill(vector<vector<int>>& grid, int src, int dst) {
  int count = 0;
  int h = grid.size();
  int w = grid[0].size();
  for (int i = 0; i < grid.size(); ++i) {
    for (int j = 0; j < grid[0].size(); ++j) {
      if (grid[i][j] != src) {
        continue;
      }
      grid[i][j] = dst;
      count++;
      queue<pair<int, int>> q;
      q.push({i, j});
      while (!q.empty()) {
        auto [i_, j_] = q.front(); q.pop();
        for (int k = 0; k < 4; ++k) {
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

void solve() {
  int N;
  scanf("%d", &N);

  set<int> hs;
  vector<vector<int>> grid(N, vector<int>(N));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      scanf("%d", &grid[i][j]);
      hs.insert(grid[i][j]);
    }
  }
  hs.erase(0);
  
  int ans = 0;
  for (auto it = hs.rbegin(); it != hs.rend(); ++it) {
    int h = *it;
    int lands = floodFill(grid, h, -1);
    if (lands > ans) {
      ans = max(ans, lands);
    }
    floodFill(grid, -1, *next(it));
  }
  printf("%d\n", ans);
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
