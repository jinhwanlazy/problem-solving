#include <bits/stdc++.h>
using namespace std;

void solve() {
  int N;
  scanf("%d", &N);

  vector<int> hs(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &hs[i]);
  }

  // dp[i][j] := i 번째 탑 까지 봤을 때, 두 탑의 높이 차이가 j인경우 두 탑중 높은 탑의 높이.
  vector<vector<int>> dp(50, vector<int>(500001, -1));
  dp[0][0] = 0;
  dp[0][hs[0]] = hs[0];
  for (int i = 1; i < N; ++i) {
    int& h = hs[i];
    for (int j = 0; j <= 500000; ++j) {
      if (dp[i-1][j] == -1) {
        continue;
      }
      
      dp[i][j] = max(dp[i][j], dp[i-1][j]);
      dp[i][j + h] = max(dp[i][j + h], dp[i-1][j] + h);
      if (h > j) {
        dp[i][h - j] = max(dp[i][h - j], dp[i-1][j] + h - j);
      } else {
        dp[i][j - h] = max(dp[i][j - h], dp[i-1][j]);
      }
    }
  }

  int ans = dp[N-1][0];
  if (ans == 0) {
    ans = -1;
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
