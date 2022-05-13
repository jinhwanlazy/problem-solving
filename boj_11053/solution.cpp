#include <bits/stdc++.h>
using namespace std;

int LIS(const vector<int>& xs) {
  vector<int> dp(xs.size(), 1);
  int res = 1;
  for (int i = 1; i < xs.size(); ++i) {
    for (int j = 0; j < i; ++j) {
      if (xs[j] < xs[i]) {
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
  vector<int> xs(N);
  for (int i = 0; i < N; ++i) {
    cin >> xs[i];
  }
  cout << LIS(xs) << "\n";
  return 0;
}
