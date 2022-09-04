#include <bits/stdc++.h>
using namespace std;

using C = complex<double>;							 // complex type for FFT

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

  vector<C> A(1<<17);
  vector<C> B(1<<17);

  for (int i = 0; i < N; ++i) {
    int a;
    scanf("%d", &a);
    A[i] = A[i + N] = C((double)a, 0);
  }
  for (int i = 0; i < N; ++i) {
    int b;
    scanf("%d", &b);
    B[N-i-1] = C{(double)b, 0};
  }

  FFT(A);
  FFT(B);
  
  for (size_t i = 0; i < A.size(); ++i) {
    A[i] *= B[i];
  }
  iFFT(A);
  double ans = 0;
  for (int i = N-1; i < 2 * N-2; ++i) {
    ans = max(ans, A[i].real());
  }

  printf("%.0f\n", ans);
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
