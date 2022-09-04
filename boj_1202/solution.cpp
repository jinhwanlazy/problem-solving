#include <bits/stdc++.h>
using namespace std;

using LL = long long;

void solve() {
  int N, K;
  scanf("%d %d", &N, &K);

  vector<pair<int, int>> mvs;
  for (int i = 0; i < N; ++i) {
    int m, v;
    scanf("%d %d", &m, &v);
    mvs.push_back({m, v});
  }

  vector<int> cs(K);
  for (int i = 0; i < K; ++i) {
    scanf("%d", &cs[i]);
  }

  sort(mvs.begin(), mvs.end());
  sort(cs.begin(), cs.end());

  priority_queue<int> pq;

  LL ans = 0;
  int i = 0;
  for (int c : cs) {
    while (i < N && mvs[i].first <= c) {
      pq.push(mvs[i].second);
      i++;
    }
    if (pq.empty()) {
      continue;
    }
    ans += pq.top();
    pq.pop();
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
