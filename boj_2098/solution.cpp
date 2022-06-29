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

  int solve() {
    set<pair<int, int>> Q;
    memo[0][1] = 0;
    Q.insert({0, 1});
    while (!Q.empty()) {
      set<pair<int, int>> Qnxt;
      for (auto [prv, mask] : Q) {
        for (int i = 0; i < N; ++i) {
          if ((mask >> i) & 1 || W[prv][i] == 0) {
            continue;
          }
          int nxt_mask = mask | (1 << i);
          memo[i][nxt_mask] = min(memo[i][nxt_mask], memo[prv][mask] + W[prv][i]);
          Qnxt.insert({i, nxt_mask});
        }
      }
      Q.swap(Qnxt);
    }
    int ans = INF;
    for (int i = 1; i < N; ++i) {
      if (W[i][0] > 0) {
        ans = min(ans, memo[i][end]+W[i][0]);
      }
    }
    return ans;
  }
    

  int N;
  vector<vector<int>> W;
  vector<vector<int>> memo;
  int end;
};

int main() {
  Solution s;
  int ans = s.solve();
  printf("%d\n", ans);

  return 0;
}
