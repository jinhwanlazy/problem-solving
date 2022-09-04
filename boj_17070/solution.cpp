#include <bits/stdc++.h>
using namespace std;

void solve() {
  int N;
  scanf("%d", &N);

  vector<vector<int>> world(N, vector<int>(N));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      scanf("%d", &world[i][j]);
    }
  }

  // dp[i][j][k] := i, j위치에 파이프를 k(가로/세로/대각선) 방향으로 놓기 위한 이동 방법의 수
  vector<vector<vector<int>>> dp(N, vector<vector<int>>(N, vector<int>(3, 0)));
  dp[0][1][0] = 1;
  for (int j = 2; j < N; ++j) {
    if (!world[0][j]) 
      dp[0][j][0] = dp[0][j-1][0];
  }
  for (int i = 1; i < N; ++i) {
    for (int j = 1; j < N; ++j) {
      if (!world[i][j]) dp[i][j][0] = dp[i][j-1][0] + dp[i][j-1][2];
      if (!world[i][j]) dp[i][j][1] = dp[i-1][j][1] + dp[i-1][j][2];
      if (!world[i][j] && !world[i-1][j] && !world[i][j-1]) {
        dp[i][j][2] = dp[i-1][j-1][0] + dp[i-1][j-1][1] + dp[i-1][j-1][2];
      }
    }
  }
  int ans = dp[N-1][N-1][0] + dp[N-1][N-1][1] + dp[N-1][N-1][2];

  //for (int i = 0; i < dp.size(); ++i) {
    //for(int j = 0; j < dp[i].size(); ++j) {
      //printf("%d/%d/%d ", dp[i][j][0], dp[i][j][1], dp[i][j][2]);
    //}
    //printf("\n");
  //}
  //printf(".\n");

  printf("%d\n", ans);
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
