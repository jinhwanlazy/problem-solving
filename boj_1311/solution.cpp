#include <bits/stdc++.h>
using namespace std;

constexpr static int INF = numeric_limits<int>::max();

struct Solution {
  Solution() {
    scanf("%d", &N);

    W.resize(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        scanf("%d", &W[i][j]);
      }
    }

    memo.resize(N, vector<int>(1 << N, INF));
  }

  int dfs(int i, int mask) {
    if (i == N) {
      return 0;
    }
    int& res = memo[i][mask];
    if (res != INF) {
      return res;
    }
    for (int j = 0; j < N; ++j) {
      if ((mask >> j) & 1) {
        continue;
      }
      res = min(res, dfs(i + 1, mask | (1 << j)) + W[i][j]);
    }
    return res;
  }

  int N;
  vector<vector<int>> W;
  vector<vector<int>> memo;
};

int main() {
  Solution s;
  cout << s.dfs(0, 0) << "\n";

  return 0;
}
