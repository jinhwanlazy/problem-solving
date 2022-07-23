#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()

using namespace std;
using LL = long long;

int main() {
  int N, M;
  scanf("%d %d", &N, &M);

  vector<vector<char>> mine(N, vector<char>(M));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      scanf(" %c", &mine[i][j]);
    }
  }

  // dp[k][i][j] := i, j 위치에서 최장으로 연결된 1의 갯수.
  // k = 0 인경우. 우하 방향
  // k = 1 인경우. 좌하 방향
  vector<vector<vector<int>>> dp(2, vector<vector<int>>(N, vector<int>(M, 0)));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      if (i == 0 || j == 0) {
        dp[0][i][j] = mine[i][j] == '1';
      }
      else {
        dp[0][i][j] = mine[i][j] == '1' ? dp[0][i-1][j-1] + 1 : 0;
      }

      if (i == 0 || j == M-1) {
        dp[1][i][j] = mine[i][j] == '1';
      }
      else {
        dp[1][i][j] = mine[i][j] == '1' ? dp[1][i-1][j+1] + 1 : 0;
      }
    }
  }

  int ans = 0;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      for (int c = ans + 1;; ++c) {
        if (dp[0][i][j] < c || dp[1][i][j] < c) {
          break;
        }
        int ii = i - (c - 1);
        int jl = j - (c - 1);
        int jr = j + (c - 1);
        if (ii < 0 || jl < 0 || jr >= M) {
          break;
        }
        if (dp[1][ii][jl] < c || dp[0][ii][jr] < c) {
          continue;
        }
        ans = max(ans, c);
      }
    }
  }

  printf("%d\n", ans);
  return 0;
}
