#include <bits/stdc++.h>
using namespace std;

constexpr static int INF = numeric_limits<int>::max();
using LL = long long;

int main() {
  int N, S;
  scanf("%d %d", &N, &S);

  vector<LL> xs(N);
  for (int i = 0; i < N; ++i) {
    scanf("%lld", &xs[i]);
  }

  int l = 0, r = 0;
  LL sum = xs[0];
  LL ans = INF;
  while (l < N) {
    while (sum < S && r < N) {
      sum += xs[++r];
    }
    if (sum >= S) {
      ans = min(ans, (LL)(r - l + 1));
    }
    sum -= xs[l++];
  }

  printf("%lld\n", ans == INF ? 0 : ans);

  return 0;
}
