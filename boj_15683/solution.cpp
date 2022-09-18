#include <bits/stdc++.h>
using namespace std;

constexpr static int INF = numeric_limits<int>::max();
constexpr static int di[4] = {0, 1, 0, -1};
constexpr static int dj[4] = {1, 0, -1, 0};

bool withinBound(const vector<vector<int>>& grid, int i, int j) {
  return 0 <= i && i < grid.size() && 0 <= j && j < grid[0].size();
};

void fillDirection(vector<vector<int>>& grid, int i, int j, int direction) {
  while (withinBound(grid, i, j) && grid[i][j] != 6) {
    if (grid[i][j] == 0) {
      grid[i][j] = 8;
    }
    i += di[direction];
    j += dj[direction];
  }
};

void simulate(vector<vector<int>>& grid,
              const pair<int, int>& cameraCoord,
              int cameraOrientation) {

  const vector<function<void(int, int)>> fn = {
    [&](int i, int j) -> void {},
    [&](int i, int j) -> void { 
      fillDirection(grid, i, j, cameraOrientation); 
    },
    [&](int i, int j) -> void { 
      fillDirection(grid, i, j, cameraOrientation); 
      fillDirection(grid, i, j, (cameraOrientation + 2) % 4); 
    },
    [&](int i, int j) -> void { 
      fillDirection(grid, i, j, cameraOrientation); 
      fillDirection(grid, i, j, (cameraOrientation + 3) % 4); 
    },
    [&](int i, int j) -> void { 
      fillDirection(grid, i, j, cameraOrientation); 
      fillDirection(grid, i, j, (cameraOrientation + 2) % 4); 
      fillDirection(grid, i, j, (cameraOrientation + 3) % 4); 
    },
    [&](int i, int j) -> void { 
      fillDirection(grid, i, j, cameraOrientation); 
      fillDirection(grid, i, j, (cameraOrientation + 1) % 4); 
      fillDirection(grid, i, j, (cameraOrientation + 2) % 4); 
      fillDirection(grid, i, j, (cameraOrientation + 3) % 4); 
    },
  };

  auto [i, j] = cameraCoord;
  int cameraType = grid[i][j];
  fn[cameraType](i, j);
}

int countBlindSpots(const vector<vector<int>>& grid) {
  int res = 0;
  for (int i = 0; i < grid.size(); ++i) {
    for(int j = 0; j < grid[i].size(); ++j) {
      res += grid[i][j] == 0;
    }
  }
  return res;
}

int countBlindSpots(vector<vector<int>> grid,
                    const vector<pair<int, int>>& cameraCoords,
                    const vector<int>& cameraOrientations) {
  for (size_t i = 0; i < cameraCoords.size(); ++i) {
    simulate(grid, cameraCoords[i], cameraOrientations[i]);
  }
  return countBlindSpots(grid);
}

void solve() {
  int N, M;
  scanf("%d %d", &N, &M);

  vector<pair<int, int>> cameraCoords;
  vector<vector<int>> grid(N, vector<int>(M));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      int& x = grid[i][j];
      scanf("%d", &x);
      if (1 <= x && x <= 5) {
        cameraCoords.push_back({i, j});
      }
    }
  }

  if (cameraCoords.empty()) {
    int ans = countBlindSpots(grid);
    printf("%d\n", ans);
    return;
  }

  int ans = INF;
  stack<vector<int>> S;
  for (int i = 0; i < 4; ++i) {
    S.push({i});
  }
  while (!S.empty()) {
    vector<int> ds = S.top();
    S.pop();
    if (ds.size() == cameraCoords.size()) {
      ans = min(ans, countBlindSpots(grid, cameraCoords, ds));
      continue;
    }
    assert (cameraCoords.size() > ds.size());
    int stride = 1;
    auto [i, j] = cameraCoords[ds.size()];
    if (grid[i][j] == 2) {
      stride = 3;
    } else if (grid[i][j] == 5) {
      stride = 4;
    }
    for (int ori = 0; ori < 4; ori += stride) {
      ds.push_back(ori);
      S.push(ds);
      ds.pop_back();
    }
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
