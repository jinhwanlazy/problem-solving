#include <bits/stdc++.h>
using namespace std;

void solve() {
  int N;
  scanf("%d", &N);

  vector<int> xs(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &xs[i]);
  }

  int ans = 0;
  for (int center = 0; center < N; ++center) {
    int r = 0;
    while (center - (r + 1) >= 0 &&                         //
           center + (r + 1) < N &&                          //
           xs[center - (r + 1)] == xs[center + (r + 1)] &&  //
           xs[center - r] > xs[center - (r + 1)])
    {
      r++;
    }
    ans = max(ans, 2 * r + 1);
  }

  for (int center = 0; center + 1 < N; ++center) {
    if (xs[center] != xs[center+1]) {
      continue;
    }
    int r = 0;
    while (center - (r + 1) >= 0 &&                         //
           center + (r + 2) < N &&                          //
           xs[center - (r + 1)] == xs[center + (r + 2)] &&  //
           xs[center - r] > xs[center - (r + 1)])
    {
      r++;
    }
    ans = max(ans, 2 * r + 2);
  }

  printf("%d\n", ans);
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
