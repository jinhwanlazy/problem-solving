#include <bits/stdc++.h>
using namespace std;

int LIS(const vector<pair<int, int>>& xs) {
  vector<int> dp(xs.size(), 1);
  int res = 1;
  for (int i = 1; i < xs.size(); ++i) {
    for (int j = 0; j < i; ++j) {
      if (xs[j].first < xs[i].first && xs[j].second < xs[i].second) {
        dp[i] = max(dp[i], dp[j] + 1);
      }
    }
    res = max(res, dp[i]);
  }
  return res;
}

int main() {
  int N;
  cin >> N;

  vector<pair<int, int>> xs(N);
  for (int i = 0; i < N; ++i) {
    cin >> xs[i].first >> xs[i].second;
  }
  sort(xs.begin(), xs.end());
  // cout << LIS(xs) << "\n";
  cout << xs.size() - LIS(xs) << "\n";
  return 0;
}
