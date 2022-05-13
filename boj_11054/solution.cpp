#include <bits/stdc++.h>
using namespace std;

vector<int> LIS(const vector<int>& xs) {
  vector<int> dp(xs.size(), 1);
  for (int i = 1; i < xs.size(); ++i) {
    for (int j = 0; j < i; ++j) {
      if (xs[j] < xs[i]) {
        dp[i] = max(dp[i], dp[j] + 1);
      }
    }
  }
  return dp;
}

int main() {
  int N;
  cin >> N;
  vector<int> xs(N);
  for (int i = 0; i < N; ++i) {
    cin >> xs[i];
  }

  auto lis_fwd = LIS(xs);
  reverse(xs.begin(), xs.end());
  auto lis_bwd = LIS(xs);
  reverse(lis_bwd.begin(), lis_bwd.end());

  int res = 0;
  for (int i = 0; i < N; ++i) {
    res = max(res, lis_fwd[i] + lis_bwd[i] - 1);
  }

  cout << res << "\n";
  return 0;
}
