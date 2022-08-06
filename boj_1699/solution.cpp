#include <bits/stdc++.h>
#include <cmath>
using namespace std;

constexpr static int INF = numeric_limits<int>::max() / 2;

void solve() {
  int N;
  scanf("%d", &N);

  vector<int> dp(N+1, INF);
  dp[0] = 0;
  dp[1] = 1;
  for (int i = 2; i <= N; ++i) {
    for (int j = 0; j * j <= i; ++j) {
      dp[i] = min(dp[i], 1 + dp[i-j*j]);
    }
  }
  printf("%d\n", dp[N]);
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
