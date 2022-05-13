#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, C;
  cin >> N >> C;

  vector<int> xs(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &xs[i]);
  }
  sort(xs.begin(), xs.end());

  int l = 0;
  int r = 1000000001;
  while (l + 1 < r) {
    int m = (l + r) / 2;

    int count = 1;
    int prev = xs[0];
    for (int i = 1; i < N; ++i) {
      if (xs[i] - prev >= m) {
        count += 1;
        prev = xs[i];
      }
    }
    if (count < C) {
      r = m;
    } else {
      l = m;
    }
  }

  cout << l << "\n";
}
