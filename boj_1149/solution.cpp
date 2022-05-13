#include <bits/stdc++.h>
using namespace std;

/*
 * dp[i][j] = i 번째 집에서 j색으로 칠했을 때의 최소의 비용
 *          = min(dp[i-1][(j+1) % 3], dp[i-1][(j+2) % 3]) + cost[i][j]
 */

int main() {
  int N;
  cin >> N;
  vector<vector<int>> costs(N, vector<int>(3));
  for (int i = 0; i < N; ++i) {
    cin >> costs[i][0] >> costs[i][1] >> costs[i][2];
  }

  vector<vector<int>> dp(N, vector<int>(3));
  for (int j = 0; j < 3; ++j) {
    dp[0][j] = costs[0][j];
  }

  for (int i = 1; i < N; ++i) {
    for (int j = 0; j < 3; ++j) {
      dp[i][j] =
          min(dp[i - 1][(j + 1) % 3], dp[i - 1][(j + 2) % 3]) + costs[i][j];
    }
  }

  int ans = dp[N - 1][0];
  ans = min(ans, dp[N - 1][1]);
  ans = min(ans, dp[N - 1][2]);
  cout << ans << "\n";
  return 0;
}
