#include <bits/stdc++.h>
using namespace std;

void solve() {
  int N, M;
  scanf("%d %d", &N, &M);

  int K;
  scanf("%d", &K);

  vector<vector<int>> lr(N, vector<int>(M, 0)), tb = lr;
  for (int i = 0; i < K; ++i) {
    int a, b, c, d;
    scanf("%d %d %d %d", &a, &b, &c, &d);
    for (int i = a - 1; i < c; ++i) {
      lr[i][b-1] += 1;
    }
    for (int j = b - 1; j < d; ++j) {
      tb[a-1][j] += 1;
    }
  }

  vector<vector<int>> dp(N, vector<int>(M, 0));
  dp[0][0] = lr[0][0];
  for (int i = 1; i < N; ++i) {
    dp[i][0] = dp[i-1][0] + tb[i][0];
  }
  for (int j = 1; j < M; ++j) {
    dp[0][j] = dp[0][j-1] + lr[0][j];
  }

  for (int i = 1; i < N; ++i) {
    for (int j = 1; j < M; ++j) {
      dp[i][j] = min(
          dp[i-1][j] + tb[i][j],
          dp[i][j-1] + lr[i][j]
      );
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
