#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  cin >> N;

  vector<pair<int, int>> ss(N);
  for (int i = 0; i < N; ++i) {
    cin >> ss[i].first >> ss[i].second;
  }

  vector<vector<int>> dp(N, vector<int>(N, numeric_limits<int>::max()));
  for (int i = 0; i < N; ++i) {
    for (int l = 0; l + i < N; ++l) {
      int r = l + i;
      if (l == r) {
        dp[l][r] = 0;
        continue;
      }
      if (l + 1 == r) {
        dp[l][r] = ss[l].first * ss[l].second * ss[r].second;
        continue;
      }
      for (int m = l; m < r; ++m) {
        int cost = ss[l].first * ss[m].second * ss[r].second;
        // cout << l << ", " << m << ", " << r << ", " << cost << "\n";
        dp[l][r] = min(dp[l][r], dp[l][m] + dp[m + 1][r] + cost);
      }
    }
  }

  if (false) {
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        cout << dp[i][j] << "\t";
      }
      cout << "\n";
    }
    cout << "\n";
  }

  cout << dp[0][N - 1] << "\n";
  return 0;
}
