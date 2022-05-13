#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  cin >> N;

  vector<vector<int>> costs(N);
  vector<vector<int>> dp(N);
  for (int i = 0; i < N; ++i) {
    costs[i].resize(i + 1);
    dp[i].resize(i + 1);
    for (int j = 0; j <= i; ++j) {
      cin >> costs[i][j];
      if (i == 0) {
        dp[i][j] = costs[i][j];
      } else {
        int prev_max = 0;
        if (j > 0) {
          prev_max = max(prev_max, dp[i - 1][j - 1]);
        }
        if (j < i) {
          prev_max = max(prev_max, dp[i - 1][j]);
        }
        dp[i][j] = prev_max + costs[i][j];
      }
      // cout << dp[i][j] << " ";
    }
    // cout << "\n";
  }
  int res = 0;
  for (int j = 0; j < N; ++j) {
    res = max(res, dp[N - 1][j]);
  }
  cout << res << "\n";
  return 0;
}
