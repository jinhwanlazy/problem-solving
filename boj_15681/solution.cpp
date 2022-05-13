#include <bits/stdc++.h>
using namespace std;

int dfs(const vector<vector<int>>& edges,
        vector<int>& parent,
        vector<int>& children,
        int u) {
  int& count = children[u];
  count = 0;
  for (int v : edges[u]) {
    if (parent[v] == -1) {
      parent[v] = u;
      count += dfs(edges, parent, children, v) + 1;
    }
  }
  return count;
}

int main() {
  int N, R, Q;
  scanf("%d %d %d", &N, &R, &Q);
  R--;

  vector<vector<int>> edges(N);
  for (int i = 0; i < N - 1; ++i) {
    int u, v;
    scanf("%d %d", &u, &v);
    u--;
    v--;
    edges[u].push_back(v);
    edges[v].push_back(u);
  }

  vector<int> parent(N, -1);
  vector<int> children(N, 0);
  parent[R] = R;

  dfs(edges, parent, children, R);

  for (int i = 0; i < Q; ++i) {
    int u;
    scanf("%d", &u);
    printf("%d\n", children[u - 1] + 1);
  }

  return 0;
}
