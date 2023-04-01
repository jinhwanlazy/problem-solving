#include <bits/stdc++.h>
using namespace std;

void solve() {
  int N, M;
  scanf("%d %d", &N, &M);

  vector<int> xs(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &xs[i]);
    if (i > 0) {
      xs[i] += xs[i-1];
    }
  }

  for (int i = 0; i < M; ++i) {
    int t;
    scanf("%d", &t);
    auto ans = upper_bound(xs.begin(), xs.end(), t) - xs.begin();
    printf("%lu\n", ans);
  }
  
  
  
  

}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
