#include <bits/stdc++.h>
using namespace std;

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
  Sieve sieve(123456 * 2 + 1);

  int n;
  while (true) {
    cin >> n;
    if (n == 0) {
      break;
    }
    size_t count(0);
    for (int i = n + 1; i <= 2 * n; ++i) {
      count += sieve.isPrime(i);
    }
    cout << count << "\n";
  }
  return 0;
}
