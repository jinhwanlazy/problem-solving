#include <bits/stdc++.h>
using namespace std;

constexpr static int INF = numeric_limits<int>::max() / 2;

struct Solution {
  Solution() {
    scanf("%d", &N);
    end = (1 << N) - 1;

    W.resize(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        scanf("%d", &W[i][j]);
      }
    }

    memo.resize(N, vector<int>(1 << N, INF));
  }

  int dfs(int last, int mask) {
    if (mask == end) {
      // NOTE there may be invalid edge!
      if (W[last][0] == 0) {
        return INF;
      }
      return W[last][0];
    }
    int& res = memo[last][mask];
    if (res != INF) {
      return res;
    }
    for (int j = 0; j < N; ++j) {
      if ((mask >> j) & 1 || W[last][j] == 0) {
        continue;
      }
      res = min(res, dfs(j, mask | (1 << j)) + W[last][j]);
    }
    return res;
  }

  int N;
  vector<vector<int>> W;
  vector<vector<int>> memo;
  int end;
};

int main() {
  Solution s;
  int ans = s.dfs(0, 1);
  printf("%d\n", ans);

  return 0;
}
