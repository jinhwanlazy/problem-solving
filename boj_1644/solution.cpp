#include <bits/stdc++.h>
using namespace std;

struct Sieve {
  Sieve(size_t max_size) : data_(max_size + 1, true) {
    data_[0] = false;
    data_[1] = false;
    for (size_t i = 2; i <= max_size; ++i) {
      if (!data_[i]) {
        continue;
      }
      for (size_t j = i * 2; j <= max_size; j += i) {
        data_[j] = false;
      }
    }
  }

  bool isPrime(size_t i) { return data_[i]; }

  vector<bool> data_;
};

int main() {
  int N;
  scanf("%d", &N);

  if (N == 1) {
    printf("0\n");
    return 0;
  }

  Sieve sieve(N);
  vector<int> primes;
  for (int i = 2; i <= N; ++i) {
    if (sieve.isPrime(i)) {
      primes.push_back(i);
    }
  }

  int l = 0;
  int r = 0;
  int sum = primes[0];
  int count = 0;
  while (l < primes.size()) {
    while (sum < N && r < primes.size() - 1) {
      sum += primes[++r];
    }
    if (sum == N) {
      count++;
    }
    sum -= primes[l++];
  }

  printf("%d\n", count);

  return 0;
}
