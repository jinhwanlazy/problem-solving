#include <bits/stdc++.h>
using namespace std;

using LL = long long;
constexpr LL MOD = LL(10e9)+7;

void solve() {
  LL N;
  scanf("%lld", &N);

  LL ans = 0;
  ans = N * (N + 1);
  ans %= MOD;
  ans *= 2 * N + 1;
  ans %= MOD;
  ans /= 3;

  ans -= (N * (N + 1) / 2) % MOD;
  ans %= MOD;
  
  //LL ans = N * (N + 1) * (2 * N + 1) / 3 - N * (N + 1) / 2;
  ans %= MOD;
  printf("%lld\n", ans * 2022);

}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    solve();
  }

  return 0;
}
