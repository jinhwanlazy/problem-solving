#include <bits/stdc++.h>
using namespace std;

void solve() {
  int N;
  scanf("%d", &N);

  vector<int> A(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &A[i]);
  }

  int ans = 1;
  vector<int> dp(N, 1);
  for (int i = 1; i < N; ++i) {
    for (int j = 0; j < i; ++j) {
      if (A[j] > A[i]) {
        dp[i] = max(dp[i], 1 + dp[j]);
      }
      ans = max(ans, dp[i]);
    }
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
