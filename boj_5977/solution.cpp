#include <bits/stdc++.h>
using namespace std;
using LL = long long;

void solve() {
  int N, K;
  scanf("%d %d", &N, &K);

  vector<LL> eSum(N+1, 0);
  for (int i = 1; i <= N; ++i) {
    scanf("%lld", &eSum[i]);
    eSum[i] += eSum[i-1];
  }

  // dp[i] := 0-i 구간에서 최대 합
  //       = max_{i-K <= j <= i} { eSum[i] - eSum[j] + dp[j-1] }
  vector<LL> dp(N+1, 0);
  deque<pair<LL, int>> dq;
  for (int i = 1; i <= N; ++i) {
    LL c = dp[i-1] - eSum[i];
    while (!dq.empty() && dq.back().first < c) dq.pop_back();
    while (!dq.empty() && dq.front().second < i-K) dq.pop_front();
    dq.push_back({c, i});
    if (i <= K) 
      dp[i] = eSum[i];
    else 
      dp[i] = eSum[i] + dq.front().first;
  }

  printf("%lld\n", dp.back());
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
