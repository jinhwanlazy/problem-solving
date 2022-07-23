#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()

using namespace std;
using LL = long long;



int main() {
  int N;
  scanf("%d", &N);

  vector<vector<int>> grid(N, vector<int>(N));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      scanf("%d", &grid[i][j]);
    }
  }

  auto isBeginning = [N](int k, int i, int j)->bool { 
    if (k % 4 == 0) return j == 0;
    else if (k % 4 == 1) return i == 0;
    else if (k % 4 == 2) return i == 0 || j == 0;
    else  return i == 0 || j == N-1;
  };

  auto prev = [N](int k, int i, int j) -> pair<int, int> {
    if (k % 4 == 0) return {i, j-1};
    else if (k % 4 == 1) return {i-1, j};
    else if (k % 4 == 2) return {i-1, j-1};
    else  return {i-1, j+1};
  };

  // dp[k][i][j] := i, j 위치에서의 최대 점수, k는 가로, 세로, 대각선, 역
  // 대각선의 네 방향과, 바꿔치기 기회를 사용했음을 나타내는 flag를 나타냄.
  vector<vector<vector<int>>> dp(8, vector<vector<int>>(N, vector<int>(N, 0)));
  int ans = 0;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      for (int k = 0; k < 8; ++k) {
        if (isBeginning(k, i, j)) {
          if (k / 4 == 0) {
            dp[k][i][j] = grid[i][j] == 1;
          }
          else {
            dp[k][i][j] = grid[i][j] == 2;
          }
        }
        else {
          auto [pi, pj] = prev(k, i, j);
          if (k / 4 == 0) {
            dp[k][i][j] = grid[i][j] == 1 ? dp[k][pi][pj] + 1 : 0;
          }
          else {
            dp[k][i][j] = max(
                grid[i][j] == 1 ? (dp[k][pi][pj] > 0 ? dp[k][pi][pj] + 1: 0) : 0,
                grid[i][j] == 2 ? dp[k-4][pi][pj] + 1 : 0);
          }
        }
        ans = max(ans, dp[k][i][j]);
      }
    }
  }

  //for (int k = 0; k < 8; ++k) {
    //printf("%d\n", k);
    //for (int i = 0; i < dp[k].size(); ++i) {
      //for(int j = 0; j < dp[k][i].size(); ++j) {
        //printf("%d ", dp[k][i][j]);
      //}
      //printf("\n");
    //}
  //}

  printf("%d\n", ans);

  return 0;
}
