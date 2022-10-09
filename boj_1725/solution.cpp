#include <bits/stdc++.h>
using namespace std;

using LL = long long;

void solve() {
  int N;
  scanf("%d", &N);

  vector<LL> hs(N);
  for (int i = 0; i < N; ++i) {
    scanf("%lld", &hs[i]);
  }
  hs.push_back(0);

  LL ans = 0;
  stack<pair<LL, LL>> S;
  for (LL i = 0; i < hs.size(); ++i) {
    const auto& h = hs[i];
    while (!S.empty() && S.top().first > h) {
      auto [h2, j] = S.top(); S.pop();
      //printf("%lld %lld %d %lld\n", j, h2, S.empty(), (S.empty() ? i : i - S.top().second - 1) * h2);
      ans = max(ans, (S.empty() ? i : i - S.top().second - 1) * h2);
    }
    if (S.empty() || S.top().first <= h) {
      S.push({h, i});
      continue;
    }
  }
  printf("%lld\n", ans);
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
