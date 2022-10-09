#include <bits/stdc++.h>
#include <cstdio>
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
  LL a, b, S;
  scanf("%lld %lld %lld", &a, &b, &S);

  // trivial case
  if (a == S || b == S || a + b == S) {
    printf("YES\n");
    return;
  }

  LL x, y, g = xGCD(a, b, x, y);
  if (S % g != 0) {
    printf("NO\n");
    return;
  }
  LL n = S / g;
  x *= n;
  y *= n;
  while (x < 1) {
    x += b;
    y -= a;
  }
  //while (y < 1) {
    //x -= b;
    //y += a;
  //}
  printf("%lld * %lld + %lld * %lld = %lld\n", x, a, y, b, x * a + y * b);
  if (y < 1 || x < 1) {
    printf("NO\n");
  }
  else {
    printf("YES\n");
  }
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
