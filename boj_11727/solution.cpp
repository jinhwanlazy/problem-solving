#include <bits/stdc++.h>
using namespace std;

constexpr static int MOD = 10007;


int main() {
  int N;
  scanf("%d", &N);
  
  vector<int> dp(N+1, 0);
  dp[1] = 1;
  dp[2] = 3;
  for (int i = 3; i <= N; ++i) {
    dp[i] = (dp[i-1] + dp[i-2] * 2) % MOD;
  }
  printf("%d\n", dp[N]);

  return 0;
}
