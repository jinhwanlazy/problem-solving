#include <bits/stdc++.h>
using namespace std;

void solve() {
  int N, M;
  scanf("%d %d", &N, &M);

  vector<vector<int>> grid(N, vector<int>(M));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      scanf("%d", &grid[i][j]);
    }
  }

  vector<vector<int>> dp(N, vector<int>(M, 0));
  dp[0][0] = grid[0][0];
  for (int j = 1; j < M; ++j) {
    dp[0][j] = grid[0][j] + dp[0][j-1];
  }
  for (int i = 1; i < N; ++i) {
    dp[i][0] = grid[i][0] + dp[i-1][0];
  }

  for (int i = 1; i < N; ++i) {
    for (int j = 1; j < M; ++j) {
      dp[i][j] = grid[i][j] + max({
          dp[i-1][j],
          dp[i][j-1],
          dp[i-1][j-1],
      });
    }
  }
  
  int ans = dp[N-1][M-1];
  printf("%d\n", ans);
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
