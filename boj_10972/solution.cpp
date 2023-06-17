#include <bits/stdc++.h>
using namespace std;

void solve() {
  int N;
  scanf("%d", &N);

  vector<int> xs(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &xs[i]);
  }

  bool isLast = true;
  for (int i = 0; i < N; ++i) {
    if (xs[i] != N - i) {
      isLast = false;
      break;
    }
  }
  if (isLast) {
    printf("-1\n");
  }
  else {
    next_permutation(xs.begin(), xs.end());
    for (int i = 0; i < xs.size(); ++i) {
      printf("%d ", xs[i]);
    }
    printf("\n");
  }
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
