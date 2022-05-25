#include <bits/stdc++.h>
using namespace std;

constexpr static int INF = numeric_limits<int>::max() >> 1;

int solve(const vector<vector<int>> costs, int start) {
  size_t N = costs[0].size();
  /* dp[i][j]: j번째 까지의 집을 색상 i로 칠했을 때의 최소비용.
   *           이 때 첫 번째 집은 start 로 칠한 것으로 함.
   */
  vector<vector<int>> dp(3, vector<int>(N, INF));
  for (int i = 0; i < 3; ++i) {
    if (i == start) {
      dp[i][0] = costs[i][0];
    }
  }
  for (int j = 1; j < N; ++j) {
    for (int i = 0; i < 3; ++i) {
      dp[i][j] = min(dp[i][j], costs[i][j] + dp[(i+1)%3][j-1]);
      dp[i][j] = min(dp[i][j], costs[i][j] + dp[(i+2)%3][j-1]);
    }
  }
  
  return min(dp[(start+1)%3][N-1], dp[(start+2)%3][N-1]);
}


int main() {
  int N;
  scanf("%d", &N);
  
  vector<vector<int>> costs(3, vector<int>(N));
  for (int j = 0; j < N; ++j) {
    for (int i = 0; i < 3; ++i) {
      scanf("%d", &costs[i][j]);
    }
  }

  int ans = min({solve(costs, 0), solve(costs, 1), solve(costs, 2)});
  printf("%d\n", ans);
  
  return 0;
}
