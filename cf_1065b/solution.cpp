#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
  ll N, M;
  scanf("%lld %lld", &N, &M);

  ll a = max(0ll, N - 2 * M);
  ll b = 0;
  for (b = 0; b < N; ++b) {
    ll e = (N - b) * (N - b - 1) / 2;
    //prllf(" - %d %d %d\n", b, e, M);
    
    if (e < M) {
      b--;
      break;
    }
  }
  printf("%lld %lld\n", a, max(0ll, b));
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
