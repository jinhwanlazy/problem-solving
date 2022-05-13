#include <bits/stdc++.h>
using namespace std;

void solve() {
  int N;
  cin >> N;
  int halfN = N / 2;
  vector<double> xs(N);
  vector<double> ys(N);
  vector<double> sign(N);
  for (int i = 0; i < N; ++i) {
    cin >> xs[i];
    cin >> ys[i];
    sign[i] = i < halfN ? -1 : 1;
  }
  double best = numeric_limits<double>::max();
  do {
    double x = 0, y = 0;
    for (int i = 0; i < N; ++i) {
      x += xs[i] * sign[i];
      y += ys[i] * sign[i];
    }
    best = min(best, x * x + y * y);
  } while (next_permutation(sign.begin(), sign.end()));
  printf("%.10f\n", sqrt(best));
}

int main() {
  int T;
  cin >> T;
  while (T--) {
    solve();
  }
  return 0;
}
