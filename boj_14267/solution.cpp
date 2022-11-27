#include <bits/stdc++.h>
using namespace std;

void solve() {
  int N, M;
  scanf("%d %d", &N, &M);

  vector<int> tree(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &tree[i]);
    if (i != 0) {
      tree[i]--;
    }
  }

  vector<int> cs(N, 0);
  for (int i = 0; i < M; ++i) {
    int root, x;
    scanf("%d %d", &root, &x);
    root--;
    cs[root] += x;
  }

  for (int i = 1; i < N; ++i) {
    cs[i] += cs[tree[i]];
  }
  for (int i = 0; i < cs.size(); ++i) {
    printf("%d ", cs[i]);
  }
  printf("\n");
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
