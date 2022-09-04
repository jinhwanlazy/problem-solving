#include <bits/stdc++.h>
#include <random>
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

void solve() {
  int W, N;
  scanf("%d %d", &W, &N);

  vector<int> parcels(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &parcels[i]);
  }

  vector<C> v(1<<20);
  for (int i : parcels) {
    v[i] = {1, 0};
  }

  FFT(v);
  for (auto& c : v) {
    c = c * c;
  }
  iFFT(v);
  for (int i : parcels) {
    v[2 * i] -= C{1, 0};
  }

  vector<int> parcels2;
  for (int i = 0; i < v.size(); ++i) {
    auto& c = v[i];
    c /= 2;
    if (round(c.real()) > 0) {
      parcels2.push_back(round(c.real()));
    }
  }
  
  FFT(v);
  for (auto& c : v) {
    c = c * c;
  }
  iFFT(v);
  //for (int i : parcels2) {
    //v[2 * i] -= C{1, 0};
  //}

  for (int i = 0; i < 100; ++i) {
    printf("%d %.0f\n", i, v[i].real());
  }
  

  printf("NO\n");
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
