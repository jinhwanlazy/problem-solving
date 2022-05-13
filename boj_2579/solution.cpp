#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  cin >> N;

  vector<int> stairs(N);
  for (int i = 0; i < N; ++i) {
    cin >> stairs[i];
  }
  /*
   * dp[i][j] := j번째 계단에서 점수의 최대값. i는 이전 step에서 1계단을
   * 올랐음을 나타내는 flag.
   */
  vector<vector<int>> dp(2, vector<int>(N, -1));
  dp[0][0] = stairs[0];
  if (N > 1) {
    dp[0][1] = stairs[1];
    dp[1][1] = stairs[0] + stairs[1];
  }
  for (int j = 2; j < N; ++j) {
    dp[0][j] = max(dp[0][j - 2], dp[1][j - 2]) + stairs[j];
    dp[1][j] = dp[0][j - 1] + stairs[j];
  }
  cout << max(dp[0][N - 1], dp[1][N - 1]) << "\n";
  return 0;
}
