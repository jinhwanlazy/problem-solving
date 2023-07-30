#include <bits/stdc++.h>
using namespace std;

using LL = long long;

void solve() {
  int N;
  scanf("%d", &N);

  LL prod = 1;
  for (int i = 0; i < N; ++i) {
    LL a;
    scanf("%lld", &a);
    prod *= a;
  }
  LL ans = LL(2022) * (prod + (LL)N - 1);
  printf("%lld\n", ans);
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    solve();
  }

  return 0;
}
