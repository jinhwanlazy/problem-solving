#include <bits/stdc++.h>
#include <cstdarg>
using namespace std;

void solve() {
  int N;
  scanf("%d", &N);

  vector<int> A(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &A[i]);
  }

  // dp[i] := i번째 수를 포함하는 증가부분수열의 합의 최대값
  vector<int> dp(N);
  dp[0] = A[0];
  int ans = A[0];
  for (int i = 1; i < N; ++i) {
    dp[i] = A[i];
    for (int j = 0; j < i; ++j) {
      if (A[j] < A[i]) {
        dp[i] = max(dp[i], A[i] + dp[j]);
      }
    }
    ans = max(ans, dp[i]);
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
