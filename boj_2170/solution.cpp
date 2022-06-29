#include <bits/stdc++.h>
using namespace std;


int main() {
  int N;
  scanf("%d", &N);

  vector<pair<int, int>> segs(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d %d", &segs[i].first, &segs[i].second);
  }

  sort(segs.begin(), segs.end());

  int ans = 0;
  pair<int, int> cur = segs.front();
  for (auto& seg : segs) {
    if (seg.first <= cur.second) {
      cur.second = max(cur.second, seg.second);
    }
    else {
      ans += cur.second - cur.first;
      cur = seg;
    }
  }
  ans += cur.second - cur.first;
  printf("%d\n", ans);
  return 0;
}
