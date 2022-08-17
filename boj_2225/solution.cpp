#include <bits/stdc++.h>
using namespace std;

using LL = long long;
constexpr static LL MOD = 1000000000;
array<array<LL, 201>, 201> dp;

template<int N, int K>
constexpr void init_table(array<array<LL, N>, K>& table) {
  for (int k = 0; k < K; ++k) {
    table[k][0] = 1;
  }
  for (int n = 1; n < N; ++n) {
    table[1][n] = 1;
  }
  for (int i = 2; i < K; ++i) {
    for (int j = 1; j < N; ++j) {
      table[i][j] = 1;
      for (int k = 0; k < j; ++k) {
        table[i][j] += table[i-1][j-k];
        table[i][j] %= MOD;
      }
    }
  }
}


void solve() {
  init_table<201, 201>(dp);

  int N, K;
  scanf("%d %d", &N, &K);

  LL ans = dp[K][N];
  printf("%lld\n", ans);
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
