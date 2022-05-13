#include <bits/stdc++.h>
using namespace std;

int solution() {
  return 0;
}
class Sieve {
 public:
  Sieve(size_t max_size) : sieve_(max_size, true) {
    sieve_[0] = false;
    sieve_[1] = false;
    for (size_t i = 2; i < max_size; ++i) {
      if (!sieve_[i]) {
        continue;
      }
      for (size_t j = i * 2; j < max_size; j += i) {
        sieve_[j] = false;
      }
    }
  }

  bool isPrime(size_t i) { return sieve_[i]; }

 private:
  vector<bool> sieve_;
};

int main() {
  int N, M;
  cin >> N >> M;

  Sieve sieve(M + 1);
  for (size_t i = N; i <= M; ++i) {
    if (sieve.isPrime(i)) {
      cout << i << "\n";
    }
  }
  return 0;
}
