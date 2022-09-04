#include <bits/stdc++.h>
using namespace std;

using LL = long long;
constexpr LL MOD = 1000000000;

int main() {
  int N;
  scanf("%d", &N);

  // dp[i][u][d] := 길이가 i이고, 마지막으로 사용된 digit이 d이고, 지금까지
  // 사용된 digit들이 (bitmask)일 때의 계단수의 갯수.
  vector<vector<vector<LL>>> dp(N+1, vector<vector<LL>>(1024, vector<LL>(10, 0)));

  // 0으로 시작할 수 없으므로 0은 생략한다.
  for (int i = 1; i < 10; ++i) {
    dp[1][1<<i][i] = 1;
  }
  for (int i = 2; i <= N; ++i) {
    for (int u = 0; u <= 1024; ++u) {
      for (int d = 0; d < 10; ++d) {
        auto& nxt = dp[i][u|(1<<d)][d];
        if (d > 0 && (u & (1 << (d - 1)))) {
          nxt += dp[i-1][u][d-1];
          nxt %= MOD;
        }
        if (d < 9 && (u & (1 << (d + 1)))) {
          nxt += dp[i-1][u][d+1];
          nxt %= MOD;
        }
      }
    }
  }

  LL ans = 0;
  for (int d = 0; d < 10; ++d) {
    ans += dp[N][1023][d];
    ans %= MOD;
  }
  printf("%lld\n", ans);

  return 0;
}
