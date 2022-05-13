#include <bits/stdc++.h>
using namespace std;

bool boundCheck(int i, int max_i) {
  return 0 <= i && i < max_i;
}

bool boundCheck(int i, int min_i, int max_i) {
  return min_i <= i && i < max_i;
}

bool boundCheck2d(int i, int j, int max_i, int max_j) {
  return boundCheck(i, max_i) && boundCheck(j, max_j);
}

bool boundCheck2d(int i, int j, int min_i, int min_j, int max_i, int max_j) {
  return boundCheck(i, min_i, max_i) && boundCheck(j, min_j, max_j);
}

int floodFill(vector<string>& grid, int i, int j) {
  const static int di[4] = {0, 0, -1, 1};
  const static int dj[4] = {-1, 1, 0, 0};
  if (grid[i][j] != '1') {
    return 0;
  }

  deque<pair<int, int>> Q{{i, j}};
  int count = 0;
  while (!Q.empty()) {
    auto coord = Q.front();
    Q.pop_front();
    int i = coord.first;
    int j = coord.second;
    if (grid[i][j] != '1') {
      continue;
    }
    grid[i][j] = '*';
    count++;
    for (int k = 0; k < 4; ++k) {
      int i2 = i + di[k];
      int j2 = j + dj[k];
      if (boundCheck2d(i2, j2, grid.size(), grid[0].size()) &&
          grid[i2][j2] == '1') {
        Q.push_back({i2, j2});
      }
    }
  }
  return count;
}

int main() {
  int N;
  scanf("%d", &N);

  vector<string> grid(N);
  for (int i = 0; i < N; ++i) {
    cin >> grid[i];
  }

  vector<int> ans;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      int count = floodFill(grid, i, j);
      if (count > 0) {
        ans.push_back(count);
      }
    }
  }

  sort(ans.begin(), ans.end());
  printf("%lu\n", ans.size());
  for (int i = 0; i < ans.size(); ++i) {
    printf("%d\n", ans[i]);
  }

  return 0;
}
