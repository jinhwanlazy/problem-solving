#include <bits/stdc++.h>
using namespace std;

int di[4] = {0, 0, -1, +1};
int dj[4] = {-1, +1, 0, 0};

int main() {
  int N, M;
  cin >> N >> M;
  vector<vector<int>> grid(N, vector<int>(M));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      cin >> grid[i][j];
    }
  }

  vector<vector<int>> dp(N, vector<int>(M, 0));
  dp[0][0] = 1;

  priority_queue<pair<int, pair<int, int>>> pq;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      pq.push({grid[i][j], {i, j}});
    }
  }
  while (!pq.empty()) {
    auto hij = pq.top();
    pq.pop();
    int height = hij.first;
    int i = hij.second.first;
    int j = hij.second.second;
    for (int k = 0; k < 4; ++k) {
      int i_ = i + di[k];
      int j_ = j + dj[k];
      if (i_ < 0 || N <= i_ || j_ < 0 || M <= j_ || height <= grid[i_][j_]) {
        continue;
      }
      // printf("%d %d %d %d %d %d\n", i, j, i_, j_, height, grid[i_][j_]);
      dp[i_][j_] += dp[i][j];
    }
  }
  // for (int i = 0; i < N; ++i) {
  // for (int j = 0; j < M; ++j) {
  // cout << dp[i][j] << "\t";
  //}
  // cout << "\n";
  //}
  // cout << "\n";

  cout << dp.back().back() << "\n";
  return 0;
}
