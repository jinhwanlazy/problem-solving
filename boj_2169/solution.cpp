#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()

using namespace std;
using LL = long long;
constexpr static int INF = numeric_limits<int>::max() >> 1;

int main() {

  int N, M;
  scanf("%d %d", &N, &M);

  vector<vector<int>> world(N, vector<int>(M));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      scanf("%d", &world[i][j]);
    }
  }

  // dp[i][j] := 위치 (i, j)에서의 최대 가치
  vector<vector<int>> dp(N, vector<int>(M, -INF));
  dp[0][0] = world[0][0];
  for (int j = 1; j < M; ++j) {
    dp[0][j] = dp[0][j-1] + world[0][j];
  }
  for (int i = 1; i < N; ++i) {
    vector<int> fromUp(M, -INF);
    for (int j = 0; j < M; ++j) { 
      fromUp[j] = dp[i-1][j] + world[i][j];
    }
    
    vector<int> left2right(M, -INF);
    left2right[0] = fromUp[0];
    for (int j = 1; j < M; ++j) {
      left2right[j] = max(fromUp[j], left2right[j-1] + world[i][j]);
    }

    vector<int> right2left(M, -INF);
    right2left[M-1] = fromUp[M-1];
    for (int j = M-2; j >= 0; --j) {
      right2left[j] = max(fromUp[j], right2left[j+1] + world[i][j]);
    }
    for (int j = 0; j < M; ++j) {
      dp[i][j] = max(left2right[j], right2left[j]);
    }
  }
  
  int ans = dp[N-1][M-1];
  printf("%d\n", ans);

  return 0;
}
