#include <bits/stdc++.h>
using namespace std;

using LL = long long;

template <typename T = long long> // xgcd
T xGCD(T a, T b, T& x, T& y) {
  if (a < b) {
    return xGCD(b, a, y, x);
  }
  if (b == 0) {
    x = 1; y = 0;
    return a;
  }
  T x_, y_, g = xGCD(b, a % b, x_, y_);
  x = y_;
  y = x_ - (a / b) * y_;
  return g;
}

void solve() {
  LL N, A;
  scanf("%lld %lld", &N, &A);

  LL ans1 = (N - A) % N;
  LL ans2 = -1;

  LL x, y, g = xGCD(N, A, x, y);
  if (g == 1) {
    ans2 = (y + N) % N;
  }
  printf("%lld %lld\n", ans1, ans2);
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
