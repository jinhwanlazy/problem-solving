#include <bits/stdc++.h>
using namespace std;

class Bishop {
  public:
    int N;
    int N2;
    vector<vector<int>> valid;
    vector<int> sums, diffs;

    Bishop(int N)
        : N(N),
          N2(N * N),
          valid(N, vector<int>(N)),
          sums(2 * N + 1, 0),
          diffs(2 * N + 1, 0) {}

    int solve(int start, int odd) {
      int ans = 0;
      for (int x = start; x < N2; ++x) {
        auto [i, j] = decode(x);
        if (odd && (i + j) % 2 != 1) {
          continue;
        }
        if (!odd && (i + j) % 2 != 0) {
          continue;
        }
        if (occupied(i, j)) {
          continue;
        }
        place(i, j);
        ans = max(ans, solve(x+1, odd) + 1);
        revert(i, j);
      }
      return ans;
    }
    
    void place(int i, int j) {
      sums[i + j] = 1;
      diffs[i - j + N - 1] = 1;
    }

    void revert(int i, int j) {
      sums[i + j] = 0;
      diffs[i - j + N - 1] = 0;
    }

    inline bool occupied(int i, int j) {
      return !valid[i][j] || sums[i + j] || diffs[i - j + N - 1];
    }
    
    inline int encode(int i, int j) const  { return i * N + j; }

    inline pair<int, int> decode(int x) const { return { x / N, x % N }; }
};

void solve() {
  int N;
  scanf("%d", &N);

  Bishop B(N);
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      int& c = B.valid[i][j];
      scanf("%d", &c);
    }
  }

  int ans = B.solve(0, true) + B.solve(0, false);
  printf("%d\n", ans);
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
