#include <bits/stdc++.h>
using namespace std;

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
  long long K, C;
  scanf("%lld %lld", &K, &C);

  if (C == 1) {
    if (K < 1e9) {
      printf("%lld\n", K+1);
    }
    else {
      printf("IMPOSSIBLE\n");
    }
    return;
  }
  if (K == 1) {
    printf("1\n");
    return;
  }

  long long x, y, g = xGCD(K, C, x, y);
  if (g != 1) {
    printf("IMPOSSIBLE\n");
    return;
  }
  while (y < 0) {
    x -= C;
    y += K;
  }
  if (y <= 1e9) {
    printf("%lld\n", y);
  }
  else {
    printf("IMPOSSIBLE\n");
  }
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    solve();
  }

  return 0;
}
