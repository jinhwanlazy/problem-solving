#include <bits/stdc++.h>
using namespace std;
using LL = long long;

constexpr static LL INF = numeric_limits<LL>::max() / 2;

void solve() {
  int N, D;
  scanf("%d %d", &N, &D);

  vector<LL> K(N+1, 0);
  for (int i = 1; i <= N; ++i) {
    scanf("%lld", &K[i]);
  }

  LL ans = -INF;
  deque<pair<LL, int>> dq;
  vector<LL> dp = K;
  for (int i = 1; i <= N; ++i) {
    dp[i] = max(dp[i], K[i] + dq.front().first);
    ans = max(ans, dp[i]);

    while (!dq.empty() && dq.back().first < dp[i]) {
      dq.pop_back();
    }
    while (!dq.empty() && dq.front().second <= i - D) {
      dq.pop_front();
    }
    dq.push_back({dp[i], i});
  }

  printf("%lld\n", ans);
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
