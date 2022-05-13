#include <bits/stdc++.h>
using namespace std;

inline bool boundCheck(int i, int max_i) {
  return 0 <= i && i < max_i;
}

inline bool boundCheck(int i, int min_i, int max_i) {
  return min_i <= i && i < max_i;
}

inline bool boundCheck2d(int i, int j, int max_i, int max_j) {
  return boundCheck(i, max_i) && boundCheck(j, max_j);
}

inline bool boundCheck2d(int i,
                         int j,
                         int min_i,
                         int min_j,
                         int max_i,
                         int max_j) {
  return boundCheck(i, min_i, max_i) && boundCheck(j, min_j, max_j);
}

void fillAir(const vector<vector<int>>& grid,
             vector<vector<int>>& air,
             int i,
             int j) {
  constexpr static int di[4] = {0, 0, -1, +1};
  constexpr static int dj[4] = {-1, +1, 0, 0};

  auto visited = air;
  queue<pair<int, int>> Q;
  Q.push({i, j});
  while (!Q.empty()) {
    auto [i, j] = Q.front();
    Q.pop();
    if (visited[i][j])
      continue;
    visited[i][j] = true;
    air[i][j] = true;
    for (int k = 0; k < 4; ++k) {
      int ii = i + di[k];
      int jj = j + dj[k];
      if (boundCheck2d(ii, jj, grid.size(), grid[0].size()) &&
          grid[ii][jj] != 1) {
        Q.push({ii, jj});
      }
    }
  }
}

int main() {
  constexpr static int di[4] = {0, 0, -1, +1};
  constexpr static int dj[4] = {-1, +1, 0, 0};

  int N, M;
  scanf("%d %d", &N, &M);

  vector<pair<int, int>> cheeses;
  vector<vector<int>> grid(N, vector<int>(M));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      scanf("%d", &grid[i][j]);
      if (grid[i][j] == 1) {
        cheeses.push_back({i, j});
      }
    }
  }
  vector<vector<int>> air(N, vector<int>(M, 0));
  fillAir(grid, air, 0, 0);

  int days = 0;
  while (!cheeses.empty()) {
    vector<pair<int, int>> survived;
    vector<pair<int, int>> dead;
    for (const auto& [i, j] : cheeses) {
      int count_air = 0;
      for (int k = 0; k < 4; ++k) {
        int ii = i + di[k];
        int jj = j + dj[k];
        if (boundCheck2d(ii, jj, N, M) && grid[ii][jj] == 0 && air[ii][jj]) {
          count_air++;
        }
      }
      if (count_air < 2) {
        survived.push_back({i, j});
      } else {
        dead.push_back({i, j});
      }
    }
    cheeses.swap(survived);
    for (const auto& [i, j] : dead) {
      grid[i][j] = 0;
      fillAir(grid, air, i, j);
    }
    days++;
  }
  printf("%d\n", days);

  return 0;
}
