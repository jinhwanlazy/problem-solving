#include <bits/stdc++.h>
using namespace std;

using LL = long long;

int main() {

  int N, M;
  scanf("%d %d", &N, &M);

  vector<pair<int, int>> segs;
  for (int i = 0; i < N; ++i) {
    int u, v;
    scanf("%d %d", &u, &v);
    if (u < v) {
      continue;
    }
    segs.push_back({v, u});
  }

  sort(segs.begin(), segs.end());

  LL ans = 0;
  LL backward = 0;
  pair<int, int> cur = segs.front();
  for (const auto& [u, v] : segs) {
    if (cur.second >= u) {
      cur.second = max(cur.second, v);
    }
    else {
      backward += LL(cur.second - cur.first);
      cur = {u, v};
    }
  }
  backward += LL(cur.second - cur.first);
  ans = (LL)M + backward * 2;
  printf("%lld\n", ans);

  return 0;
}
