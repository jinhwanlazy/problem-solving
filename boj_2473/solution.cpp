#include <bits/stdc++.h>
using namespace std;

using LL = long long;
constexpr static LL INF = numeric_limits<LL>::max();

struct Ans {
  LL a, b, c;
  LL sum;

  bool operator<(const Ans& rhs) const {
    return abs(sum) < abs(rhs.sum);
  }
};

void solve() {
  int N;
  scanf("%d", &N);

  vector<LL> xs(N);
  for (int i = 0; i < N; ++i) {
    scanf("%lld", &xs[i]);
  }

  sort(xs.begin(), xs.end());
  Ans ans = {-1, -1, -1, INF};

  for (int i = 0; i < N-1; ++i) {
    for (int j = i+1; j < N; ++j) {
      LL s = xs[i] + xs[j];
      int k = lower_bound(xs.begin() + j + 1, xs.end(), -s) - xs.begin();
      for (int dk = -1; dk <= 1; ++dk) {
        auto kk = k + dk;
        if (kk < 0 || kk >= N || kk == i || kk == j) {
          continue;
        }
        ans = min(ans, {xs[i], xs[j], xs[kk], s + xs[kk]});
      }
    }
  }
  printf("%lld %lld %lld\n", ans.a, ans.b, ans.c);

}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
