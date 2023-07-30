#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

void solve() {
  int N;
  scanf("%d", &N);

  vector<int> xs(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &xs[i]);
  }

  if (prev_permutation(xs.begin(), xs.end())) {
    for (int i = 0; i < xs.size(); ++i) {
      printf("%d ", xs[i]);
    }
    printf("\n");
  }
  else {
    printf("-1\n");
  }
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
