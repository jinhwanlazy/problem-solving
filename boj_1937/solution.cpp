#include <bits/stdc++.h>
using namespace std;

constexpr static int di[4] = {0, 1, 0, -1};
constexpr static int dj[4] = {1, 0, -1, 0};

int dfs(const vector<vector<int>>& W, vector<vector<int>>& dp, int i, int j) {
  int& res = dp[i][j];
  if (res != 0) {
    return res;
  }
  res = 1;
  for (int k = 0; k < 4; ++k) {
    int ii = i + di[k];
    int jj = j + dj[k];
    if (ii < 0 || W.size() <= ii) {
      continue;
    }
    if (jj < 0 || W[0].size() <= jj) {
      continue;
    }
    if (W[i][j] < W[ii][jj]) {
      res = max(res, 1 + dfs(W, dp, ii, jj));
      
    }
  }
  return res;
}


void solve() {
  int N;
  scanf("%d", &N);

  vector<vector<int>> W(N, vector<int>(N));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      scanf("%d", &W[i][j]);
    }
  }

  vector<vector<int>> dp(N, vector<int>(N, 0));
  int ans = -1;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      ans = max(ans, dfs(W, dp, i, j));
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
