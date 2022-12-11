#include <bits/stdc++.h>
using namespace std;

template <typename T = unsigned long long>
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

bool isPrime(unsigned long long n) {
  using ULL = unsigned long long;
  if (n <= 1) return false;
  if (n <= 3) return true;
  if (n % 2 == 0) return false;

  int s = 0;
  ULL d = n - 1;
  while (d % 2 == 0) {
    s++;
    d >>= 1;
  }

  const auto _millerRabinTest = [n, s, d](ULL a) -> bool {
    ULL x = modPow(a, d, n);
    for (int i = 0; i < s; ++i) {
      ULL y = (x * x) % n;
      if (y == 1 && x != 1 && x != n - 1) 
        return false;
      x = y;
    }
    return x == 1;
  };

  vector<ULL> testSet;
  if (n < 2'047ull) testSet = {2};
  else if (n < 1'373'653ull) testSet = {2, 3};
  else if (n < 4'759'123'141ull) testSet = {2, 7, 61};
  else if (n < 341'550'071'728'321ull) testSet = {2, 3, 5, 7, 11, 13, 17};
  else testSet = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
  
  for (const auto a : testSet) {
    if (!_millerRabinTest(a)) {
      return false;
    }
  }
  return true;
}

void solve() {
  int N;
  scanf("%d", &N);

  int count = 0;
  while (N--) {
    unsigned long long x;
    scanf("%llu", &x);

    count += isPrime(2 * x + 1);
  }
  printf("%d\n", count);
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
