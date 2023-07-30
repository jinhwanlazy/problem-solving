#include <bits/stdc++.h>
using namespace std;

long long dp[4][1001][1001];
constexpr long long mod = 998244353;

void solve() {
  int W, H;
  scanf("%d %d", &W, &H);

  vector<vector<vector<long long>>> dp(
      4, vector<vector<long long>>(H, vector<long long>(W, 0)));
  // 0: tl
  // 1: bl
  // 2: br
  // 3: tr
  
  for (int i = 0; i < H; ++i) {
    for (int j = 0; j < W; ++j) {
      if (i == 0 && j == 0) {
        for (int k = 0; k < 4; ++k) {
          dp[k][i][j] = 1;
        }
      }
      else if (i == 0) {
        dp[0][i][j] = (dp[0][i][j-1] + dp[1][i][j-1]) % mod;
        dp[1][i][j] = (dp[0][i][j-1] + dp[1][i][j-1]) % mod;
        dp[2][i][j] = (dp[2][i][j-1] + dp[3][i][j-1]) % mod;
        dp[3][i][j] = (dp[2][i][j-1] + dp[3][i][j-1]) % mod;
      }
      else if (j == 0) {
        dp[0][i][j] = (dp[0][i-1][j] + dp[3][i-1][j]) % mod;
        dp[1][i][j] = (dp[1][i-1][j] + dp[2][i-1][j]) % mod;
        dp[2][i][j] = (dp[1][i-1][j] + dp[2][i-1][j]) % mod;
        dp[3][i][j] = (dp[0][i-1][j] + dp[3][i-1][j]) % mod;
      }
      else {
        for (int k = 0; k < 4; ++k) {
          for (int l = 0; l < 4; ++l) {
            dp[k][i][j] += dp[l][i-1][j-1];
            dp[k][i][j] %= mod;
          }
        }
      }
    }
  }

  long long ans = 0;
  for (int k = 0; k < 4; ++k) {
    ans += dp[k][H-1][W-1];
    ans %= mod;
  }
  cout << ans << "\n";
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
