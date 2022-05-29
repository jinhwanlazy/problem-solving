#include <bits/stdc++.h>
using namespace std;

void solve() {
  int N;
  scanf("%d", &N);
  
  vector<int> parent(N, -1);
  vector<vector<int>> children(N);
  for (int i = 0; i < N-1; ++i) {
    int u, v;
    scanf("%d %d", &u, &v);
    u--; v--;
    parent[v] = u;
    children[u].push_back(v);
  }

  vector<int> depth(N, 0);
  stack<pair<int, int>> S;
  for (int i = 0; i < N; ++i) {
    if (parent[i] == -1) {
      S.push({i, 0});
      break;
    }
  }

  while (!S.empty()) {
    auto [i, d] = S.top(); S.pop();
    depth[i] = d;
    for (int child : children[i]) {
      S.push({child, d+1});
    }
  }
  
  int u, v;
  scanf("%d %d", &u, &v);
  u--;
  v--;

  while (depth[u] > depth[v] && depth[u] != 0) {
    u = parent[u];
  }

  while (depth[u] < depth[v] && depth[v] != 0) {
    v = parent[v];
  }

  while (u != v) {
    u = parent[u];
    v = parent[v];
  }

  printf("%d\n", u+1);
}


int main() {
  int T;
  scanf("%d", &T);
  
  while (T--) {
    solve();
  }

  return 0;
}
