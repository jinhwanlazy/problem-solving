#include <bits/stdc++.h>
using namespace std;

using C = complex<double>; // complex type for FFT

void FFT(vector<C>& v, bool inv = false) {
  size_t n = v.size();
  for (size_t i = 1, j = 0; i < n; ++i) {
    size_t b = n >> 1;
    while (!((j ^= b) & b))
      b >>= 1;
    if (i < j)
      swap(v[i], v[j]);
  }
  for (size_t k = 1; k < n; k <<= 1) {
    C::value_type a = (inv ? 1.0 : -1.0) * M_PI / (C::value_type)k;
    C w(cos(a), sin(a));
    for (size_t i = 0; i < n; i += (k << 1)) {
      C wp(1, 0);
      for (size_t j = 0; j < k; ++j) {
        C x = v[i + j];
        C y = v[i + j + k] * wp;
        v[i + j] = x + y;
        v[i + j + k] = x - y;
        wp *= w;
      }
    }
  }
  if (inv) {
    for (size_t i = 0; i < n; ++i)
      v[i] /= (C::value_type)n;
  }
}

void iFFT(vector<C>& f) {
  return FFT(f, 1);
}

inline vector<int> readv() {
  int N;
  scanf("%d", &N);
  
  vector<int> xs(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &xs[i]);
    xs[i] += 30000;
  }

  return xs;
}

void solve() {
  auto a = readv();
  auto b = readv();
  auto c = readv();

  const int M = 1 << 17;

  vector<C> cA(M), cB2(M), cC(M);
  vector<int> b2(M);
  for (size_t i = 0; i < a.size(); ++i) {
    cA[a[i]] = {1, 0};
  }
  for (size_t i = 0; i < b.size(); ++i) {
    b2[b[i] * 2] = 1;
  }
  for (size_t i = 0; i < c.size(); ++i) {
    cC[c[i]] = {1, 0};
  }

  FFT(cA);
  FFT(cC);
  for (size_t i = 0; i < M; ++i) {
    cB2[i] = cA[i] * cC[i];
  }
  iFFT(cB2);
  
  int ans = 0;
  for (size_t i = 0; i < M; ++i) {
    int x = round(cB2[i].real());
    if (x > 0 && b2[i] > 0) {
      ans += x;
    }
  }
  printf("%d\n", ans);
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
