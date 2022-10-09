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

template <typename T = unsigned long long> // modpow
T modPow(T base, T exp, T mod) {
  if (exp == 0) {
    return 1;
  }
  if (exp == 1) {
    return base % mod;
  }
  
  T res = modPow(base, exp / 2, mod);
  res = res * res;
  res %= mod;
  if (exp & 1) {
    res *= base;
    res %= mod;
  }
  return res;
}

LL mod(LL a, LL m)  {
  return ((a % m) + m) % m;
}

void solve() {
  LL m, S, X1, X2;
  scanf("%lld %lld %lld %lld", &m, &S, &X1, &X2);

  LL a = (X1 - X2) * modPow(S - X1, m-2, m);
  a = mod(a, m);

  LL c = X1 - a * S;
  c = mod(c, m);

  printf("%lld %lld\n", a, c);
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
