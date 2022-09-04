#include <bits/stdc++.h>
using namespace std;

constexpr unsigned FFT_N_MAX = 1 << 19;  // 524288
using C = complex<double>;               // complex type for FFT

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
  int N;
  scanf("%d", &N);

  vector<int> distances(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &distances[i]);
  }

  int M;
  scanf("%d", &M);

  vector<int> holes(M);
  for (int i = 0; i < M; ++i) {
    scanf("%d", &holes[i]);
  }

  vector<C> v(FFT_N_MAX, 0);
  for (int k : distances) {
    v[k] = 1;
  }

  set<int> reachableHoles;
  for (int h : holes) {
    if (v[h].real() > 0) {
      reachableHoles.insert(h);
    }
  }

  // convolution in frequency domain
  FFT(v);
  for_each(v.begin(), v.end(), [](auto& c) { c = c * c; });
  iFFT(v);

  for (int h : holes) {
    if (v[h].real() > 1e-6) {
      reachableHoles.insert(h);
    }
  }

  printf("%lu\n", reachableHoles.size());
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
