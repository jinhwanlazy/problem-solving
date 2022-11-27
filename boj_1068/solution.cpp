#include <bits/stdc++.h>
using namespace std;

int countLeaves(const vector<vector<int>>& tree, int root) {
  if (tree[root].empty()) {
    return 1;
  }
  int res = 0;
  for (int i : tree[root]) {
    res += countLeaves(tree, i);
  }
  return res;
}

void solve() {
  int N;
  scanf("%d", &N);

  vector<int> parent(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &parent[i]);
  }

  int K;
  scanf("%d", &K);

  int root = -1;
  vector<vector<int>> children(N);
  for (int i = 0; i < N; ++i) {
    if (parent[i] == -1) {
      root = i;
    } else if (i != K && parent[i] != K) {
      children[parent[i]].push_back(i);
    }
  }
  
  if (K == root) {
    printf("%d\n", 0);
  }
  else {
    int ans = countLeaves(children, root);
    printf("%d\n", ans);
  }
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
