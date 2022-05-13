/*
 * 1  2  3  4  5  6 ...
 * 2  4  6  8 10 12 ...
 * 3  6  9 12 15 18 ...
 * 4  8 12 16 20 24 ...
 * 5 10 15 20 25 30 ...
 * 6 12 18 24 30 36 ...
 * 7 14 21 28 35 42 ...
 * ....................
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, K;
  cin >> N >> K;

  int l = 1;
  int r = 1000000001;

  while (l + 1 < r) {
    int m = (l + r) / 2;
    int count = 0;
    for (int i = 1; i <= N; ++i) {
      count += min(N, (m - 1) / i);
    }
    // cout << l << ", " << m << ", " << r << " - " << count << "\n";
    if (count < K) {
      l = m;
    } else {
      r = m;
    }
  }
  cout << l << "\n";
  return 0;
}
