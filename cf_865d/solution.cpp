#include <bits/stdc++.h>
using namespace std;

using LL = long long;

void solve() {
  int N;
  scanf("%d", &N);

  priority_queue<int> pq;

  LL ans = 0;
  for (int i = 0; i < N; ++i) {
    int p;
    scanf("%d", &p);
    pq.push(-p);
    int m = -pq.top();
    if (p > m) {
      pq.pop();
      ans += (LL)(p - m);
      pq.push(-p);
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
