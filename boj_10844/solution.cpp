#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  cin >> N;

  /*
   * dp[i][j] := 길이가 j이고 마지막 숫자가 i인 최대 계단수
   * dp[i][j] = dp[i-1][j-1] + dp[i+1][j-1]
   */

  constexpr int MOD = 1000000000;
  vector<vector<int>> dp(10, vector<int>(N + 1));
  for (int i = 0; i < 9; ++i) {
    dp[i][1] = 1;
  }
  for (int j = 2; j <= N; ++j) {
    for (int i = 0; i <= 9; ++i) {
      if (i > 0) {
        dp[i][j] += dp[i - 1][j - 1];
      }
      if (i < 9) {
        dp[i][j] += dp[i + 1][j - 1];
      }
      dp[i][j] %= MOD;
    }
  }
  int res = 0;
  for (int i = 0; i <= 9; ++i) {
    res += dp[i][N];
    res %= MOD;
  }
  cout << res << "\n";
  return 0;
}
