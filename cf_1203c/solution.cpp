#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int countdivisors(ll x) {
  int res = 0;
  for (ll i = 1; i * i <= x; ++i) {
    if (i * i == x) {
      res += 1;
    }
    else if (x % i == 0) {
      res += 2;
    }
  }
  return res;
}

void solve() {
  int n;
  scanf("%d", &n);
  
  vector<ll> xs(n);
  for (int i = 0; i < n; ++i) {
    scanf("%lld", &xs[i]);
  }

  ll div = xs[0];
  for (ll x : xs) {
    div = gcd(div, x);
  }
  int ans = countdivisors(div);
  printf("%d\n", ans);

}

int main() {
  int t = 1;
  while (t--) {
    solve();
  }

  return 0;
}
