#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int solve() {
  int N;
  scanf("%d", &N);
  
  vector<vector<int>> S(2, vector<int>(N));
  for (int row = 0; row < 2; ++row) {
    for (int i = 0; i < N; ++i) {
      scanf("%d", &S[row][i]);
    }
  }
  
  if (N == 1) {
    return max(S[0][0], S[1][0]);
  }
  if (N == 2) {
    return max(S[0][0] + S[1][1], S[1][0] + S[0][1]);
  }

  // dp[i][j] := j열에서 i행의 스티커를 선택했을 때 0-j 범위에서 얻을 수 있는 가장 큰 점수. 
  vector<vector<int>> dp(2, vector<int>(N, 0));
  dp[0][0] = S[0][0];
  dp[1][0] = S[1][0];
  dp[0][1] = S[1][0] + S[0][1];
  dp[1][1] = S[0][0] + S[1][1];

  for (int j = 2; j < N; ++j) {
    dp[0][j] = max({
        dp[1][j-1] + S[0][j], 
        dp[0][j-2] + S[0][j], 
        dp[1][j-2] + S[0][j]});
    dp[1][j] = max({
        dp[0][j-1] + S[1][j], 
        dp[0][j-2] + S[1][j], 
        dp[1][j-2] + S[1][j]});
  }
  return max(dp[0][N-1], dp[1][N-1]);
}

int main() {
  int T;
  scanf("%d", &T);

  while (T--) {
    int ans = solve();
    printf("%d\n", ans);
  }

  return 0;
}
