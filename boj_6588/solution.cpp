#include <bits/stdc++.h>
using namespace std;

template <unsigned MAX_N> // algsieve
class Sieve {
  array<bool, MAX_N+1> sieve_;

public:
  constexpr Sieve() : sieve_{} {
    fill(sieve_.begin(), sieve_.end(), true);
    sieve_[0] = false;
    sieve_[1] = false;
    for (size_t i = 2; i <= MAX_N; ++i) {
      if (!sieve_[i]) {
        continue;
      }
      for (size_t j = i * 2; j <= MAX_N; j += i) {
        sieve_[j] = false;
      }
    }
  }

  constexpr bool isPrime(size_t i) const {
    return sieve_[i];
  }
};

void solve() {
  Sieve<1000000> sieve;
  vector<int> primes;
  for (int i = 3; i <= 1000000; ++i) {
    if (sieve.isPrime(i)) {
      primes.push_back(i);
    }
  }

  while (true) {
    int n;
    scanf("%d", &n);

    if (n == 0) {
      break;
    }

    for (int a : primes) {
      int b = n - a;
      if (sieve.isPrime(b)) {
        printf("%d = %d + %d\n", n, a, b);
        break;
      }
    }
  }

}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
