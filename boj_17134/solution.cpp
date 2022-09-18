#include <bits/stdc++.h>
using namespace std;

struct Sieve {
  Sieve(size_t max_size) : data_(max_size, true) {
    data_[0] = false;
    data_[1] = false;
    for (size_t i = 2; i < max_size; ++i) {
      if (!data_[i]) {
        continue;
      }
      for (size_t j = i * 2; j < max_size; j += i) {
        data_[j] = false;
      }
    }
  }
  
  bool isPrime(size_t i) {
    return data_[i];
  }
  
  vector<bool> data_;
};

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

int main() {
  Sieve sieve(1000001);

  const int M = 1 << 21;
  vector<C> evenSemiPrimes(M);
  for (size_t i = 2; i * 2 < sieve.data_.size(); ++i) {
    if (sieve.isPrime(i)) {
      evenSemiPrimes[2 * i] = C{1, 0};
    }
  }

  vector<C> oddPrimes(M);
  for (size_t i = 3; i < sieve.data_.size(); ++i) {
    if (sieve.isPrime(i)) {
      oddPrimes[i] = C{1, 0};
    }
  }

  vector<C> res(M);

  FFT(oddPrimes);
  FFT(evenSemiPrimes);
  for (int i = 0; i < M; ++i) {
    res[i] = oddPrimes[i] * evenSemiPrimes[i];
  }
  iFFT(res);
  
  int T;
  scanf("%d", &T);
  while (T--) {
    int N;
    scanf("%d", &N);
    printf("%d\n", (int)round(res[N].real()));
  }

  return 0;
}
