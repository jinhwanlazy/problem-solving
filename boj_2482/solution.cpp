#include <bits/stdc++.h>
using namespace std;

constexpr static int MOD = 1000000003;

int main() {
  int N, K;
  scanf("%d %d", &N, &K);

  // dp[i][j] := i개의 색상중 k개의 고르는 경우의 수. 일단 원형조건은 생각치
  // 않고 계산.
  vector<vector<int>> dp(N+1, vector<int>(K+1, 0));
  for (int i = 1; i <= N; ++i) {
    dp[i][0] = 1;
  }
  for (int i = 1; i <= N; ++i) {
    dp[i][1] = i;
  }
  for (int i = 2; i <= N; ++i) {
    for (int j = 2; j <= K; ++j) {
      dp[i][j] = (dp[i-2][j-1] + dp[i-1][j]) % MOD;
    }
  }

  // if (1번째 색상을 고르지 않은 경우):
  //    1번째를 제외하고 나머지  N-1개의 색상 중 K개를 고른 경우와 같다.
  // if (1번째 생상을 고른 경우): 
  //     1, 2번째와 N번 째를 제외한 N-3개의 색상중 K-1개를 고른 경우와 같다.
  int ans = (dp[N-1][K] + dp[N-3][K-1]) % MOD;
  printf("%d\n", ans);
  
  return 0;
}
