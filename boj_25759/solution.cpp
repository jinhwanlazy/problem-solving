#include <bits/stdc++.h>
using namespace std;

void solve() {
  int N;
  scanf("%d", &N);

  vector<int> A(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &A[i]);
  }

  vector<vector<int>> dp(N, vector<int>(101, -1));
  dp[0][A[0]] = 0;
  for (int i = 1; i < N; ++i) {
    for (int j = 1; j <= 100; ++j) {
      if (dp[i-1][j] == -1) {
        continue;
      }
      dp[i][j] = max(dp[i][j], dp[i-1][j]);
      dp[i][A[i]] = max(dp[i][A[i]], dp[i-1][j] + (A[i] - j) * (A[i] - j));
    }
  }

  int ans = 0;
  for(int j = 1; j <= 100; ++j) {
    ans = max(ans, dp[N-1][j]);
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
