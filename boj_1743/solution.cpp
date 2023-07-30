#include <bits/stdc++.h>
using namespace std;

constexpr static int di[4] = {0, 1, 0, -1};
constexpr static int dj[4] = {1, 0, -1, 0};

int floodFill(vector<vector<int>>& grid, int src, int dst) {
  int max_size = 0;
  int count = 0;
  int h = grid.size();
  int w = grid[0].size();
  for (int i = 0; i < grid.size(); ++i) {
    for (int j = 0; j < grid[0].size(); ++j) {
      if (grid[i][j] != src) {
        continue;
      }
      count++;
      grid[i][j] = dst;
      int local = 1;
      queue<pair<int, int>> q;
      q.push({i, j});
      while (!q.empty()) {
        auto [i_, j_] = q.front();
        q.pop();
        for (int k = 0; k < 4; ++k) {
          int ii = i_ + di[k];
          int jj = j_ + dj[k];
          if (0 <= ii && ii < h && 0 <= jj && jj < w && grid[ii][jj] == src) {
            grid[ii][jj] = dst;
            q.push({ii, jj});
            local += 1;
          }
        }
      }
      max_size = max(max_size, local);
    }
  }
  return max_size;
}

void solve() {
  int N, M, K;
  scanf("%d %d %d", &N, &M, &K);

  vector<vector<int>> grid(N, vector<int>(M, 0));
  for (int i = 0; i < K; ++i) {
    int r, c;
    scanf("%d %d", &r, &c);
    grid[--r][--c] = 1;
  }

  int ans = floodFill(grid, 1, 0);
  printf("%d\n", ans);
  
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
