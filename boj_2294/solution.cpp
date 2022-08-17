#include <bits/stdc++.h>
using namespace std;

constexpr static int INF = numeric_limits<int>::max() / 2;

void solve() {
  int N, K;
  scanf("%d %d", &N, &K);

  vector<int> coins(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &coins[i]);
  }

  vector<int> dp(K+1, INF);
  dp[0] = 0;
  for (int i = 1; i <= K; ++i) {
    for (int c : coins) {
      if (i - c >= 0) {
        dp[i] = min(dp[i], dp[i - c] + 1);
      }
    }
  }
  if (dp[K] == INF) {
    printf("-1\n");
  }
  else {
    printf("%d\n", dp[K]);
  }

}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
