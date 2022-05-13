#include <bits/stdc++.h>
using namespace std;

constexpr static int INF = numeric_limits<int>::max();

struct Coord {
  int i, j;

  friend istream& operator>>(istream& is, Coord& rhs) {
    is >> rhs.i >> rhs.j;
    return is;
  }

  int distance(const Coord& other) {
    return abs(i - other.i) + abs(j - other.j);
  }
};

int main() {
  int N, W;
  scanf("%d %d", &N, &W);

  vector<Coord> cases(W + 1);
  for (int i = 1; i <= W; ++i) {
    cin >> cases[i];
  }

  /*
   * dp[i][j] := 두 차량이 각각 i, j번째 사건 장소에 있을 때 최소 cost
   */
  vector<vector<int>> dp(W + 1, vector<int>(W + 1, INF / 2));
  vector<vector<pair<int, int>>> trace(W + 1, vector<pair<int, int>>(W + 1));
  dp[1][0] = Coord{1, 1}.distance(cases[1]);
  trace[1][0] = {0, 0};
  dp[0][1] = Coord{N, N}.distance(cases[1]);
  trace[0][1] = {0, 0};

  for (int i = 0; i <= W; ++i) {
    for (int j = 0; j <= W; ++j) {
      if (i == j) {
        continue;
      }
      if (i < j && j + 1 <= W) {
        int i_step = (i == 0 ? Coord{1, 1} : cases[i]).distance(cases[j + 1]);
        if (dp[j + 1][j] > dp[i][j] + i_step) {
          dp[j + 1][j] = dp[i][j] + i_step;
          trace[j + 1][j] = {i, j};
        }
        int j_step = (j == 0 ? Coord{N, N} : cases[j]).distance(cases[j + 1]);
        if (dp[i][j + 1] > dp[i][j] + j_step) {
          dp[i][j + 1] = dp[i][j] + j_step;
          trace[i][j + 1] = {i, j};
        }
      }
      if (i > j && i + 1 <= W) {
        int i_step = (i == 0 ? Coord{1, 1} : cases[i]).distance(cases[i + 1]);
        if (dp[i + 1][j] > dp[i][j] + i_step) {
          dp[i + 1][j] = dp[i][j] + i_step;
          trace[i + 1][j] = {i, j};
        }
        int j_step = (j == 0 ? Coord{N, N} : cases[j]).distance(cases[i + 1]);
        if (dp[i][i + 1] > dp[i][j] + j_step) {
          dp[i][i + 1] = dp[i][j] + j_step;
          trace[i][i + 1] = {i, j};
        }
      }
    }
  }

  int i = 0, j = W;
  for (int k = 0; k < W; ++k) {
    if (dp[k][W] < dp[i][j]) {
      i = k;
      j = W;
    }
    if (dp[W][k] < dp[i][j]) {
      i = W;
      j = k;
    }
  }

  printf("%d\n", dp[i][j]);
  vector<int> ans;
  do {
    int ii = trace[i][j].first;
    int jj = trace[i][j].second;
    ans.push_back(ii == i ? 2 : 1);
    i = ii;
    j = jj;
  } while (i != 0 || j != 0);

  reverse(ans.begin(), ans.end());
  for (int i = 0; i < ans.size(); ++i) {
    printf("%d\n", ans[i]);
  }

  return 0;
}
