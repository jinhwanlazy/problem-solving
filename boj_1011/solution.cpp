#include <bits/stdc++.h>
using namespace std;

void floodFill(vector<vector<int>>& field, int x, int y) {
  std::deque<pair<int, int>> Q;
  field[y][x] = 0;
  Q.push_back({x, y});
  while (!Q.empty()) {
    auto coord = Q.front();
    x = coord.first;
    y = coord.second;
    Q.pop_front();
    if (x + 1 < field[0].size() && field[y][x + 1]) {
      field[y][x + 1] = 0;
      Q.push_back({x + 1, y});
    }
    if (x - 1 >= 0 && field[y][x - 1]) {
      field[y][x - 1] = 0;
      Q.push_back({x - 1, y});
    }
    if (y + 1 < field.size() && field[y + 1][x]) {
      field[y + 1][x] = 0;
      Q.push_back({x, y + 1});
    }
    if (y - 1 >= 0 && field[y - 1][x]) {
      field[y - 1][x] = 0;
      Q.push_back({x, y - 1});
    }
  }
}

void solve() {
  int M, N, K;
  cin >> M >> N >> K;
  vector<vector<int>> field(N, vector<int>(M, 0));
  for (int i = 0; i < K; ++i) {
    int x, y;
    cin >> x >> y;
    field[y][x] = 1;
  }

  int countWorm = 0;
  for (int y = 0; y < N; ++y) {
    for (int x = 0; x < M; ++x) {
      if (field[y][x]) {
        floodFill(field, x, y);
        countWorm++;
      }
    }
  }
  cout << countWorm << "\n";
}

int main() {
  int T;
  cin >> T;
  while (T--) {
    solve();
  }
  return 0;
}
