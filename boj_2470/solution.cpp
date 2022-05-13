#include <bits/stdc++.h>
using namespace std;

using LL = long long;

int main() {
  int N;
  scanf("%d", &N);

  vector<LL> xs(N);
  for (int i = 0; i < N; ++i) {
    scanf("%lld", &xs[i]);
  }

  sort(xs.begin(), xs.end());

  int l = 0;
  int r = N - 1;
  double ans = numeric_limits<double>::max();
  int ans_l, ans_r;
  while (l < r) {
    while (xs[l] + xs[r] > 0 && r > l + 1) {
      int s = abs(xs[l] + xs[r]);
      if (s < ans) {
        ans = s;
        ans_l = xs[l];
        ans_r = xs[r];
      }
      r--;
    }
    while (xs[l] + xs[r] < 0 && r < N - 1) {
      int s = abs(xs[l] + xs[r]);
      if (s < ans) {
        ans = s;
        ans_l = xs[l];
        ans_r = xs[r];
      }
      r++;
    }
    int s = abs(xs[l] + xs[r]);
    if (s < ans) {
      ans = s;
      ans_l = xs[l];
      ans_r = xs[r];
    }
    l++;
  }

  printf("%d %d\n", ans_l, ans_r);

  return 0;
}
