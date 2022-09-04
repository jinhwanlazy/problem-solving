#include <bits/stdc++.h>
using namespace std;

using LL = long long;

void solve() {
  int N, S;
  scanf("%d %d", &N, &S);

  vector<int> xs(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &xs[i]);
  }

  vector<LL> dp_(100'000 * 100, 0);
  LL* dp = &dp_[100'000 * 50];
  
  for (int x : xs) {
    if (x > 0) {
      for (int i = 4000000; i >= -4000000; --i) {
        dp[i] += dp[i-x];
      }
    }
    else {
      for (int i = -4000000; i <= 4000000; ++i) {
        dp[i] += dp[i-x];
      }
    }
    dp[x] += 1;
  }

  printf("%lld\n", dp[S]);
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
