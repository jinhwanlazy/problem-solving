#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  scanf("%d", &N);

  vector<vector<LL>> dp(10, vector<LL>(N + 1, 0));
  for (int i = 1; i < 10; ++i) {
    dp[i][1] = 1;
  }
  for (int j = 2; j <= N; ++j) {
    for (int i = 0; i < 10; ++i) {
      if (i > 0) {
        dp[i][j] += dp[i - 1][j - 1];
      }
      if (i < 9) {
        dp[i][j] += dp[i + 1][j - 1];
      }
    }
  }

  LL ans = 0;
  for (int i = 0; i < 10) {
    ans += dp[i][N];
  }
  printf("%d\n", ans);

  return 0;
}
