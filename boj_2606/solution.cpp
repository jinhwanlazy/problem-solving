#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, M;
  scanf("%d %d", &N, &M);

  vector<vector<int>> edges(N + 1);

  for (int i = 0; i < M; ++i) {
    int a, b;
    scanf("%d %d", &a, &b);
    edges[a].push_back(b);
    edges[b].push_back(a);
  }

  vector<bool> visited(N + 1, false);
  vector<int> S{1};
  int ans = 0;
  while (!S.empty()) {
    int u = S.back();
    S.pop_back();
    if (visited[u]) {
      continue;
    }
    visited[u] = true;
    ans++;
    for (int v : edges[u]) {
      if (!visited[v]) {
        S.push_back(v);
      }
    }
  }
  printf("%d\n", ans - 1);

  return 0;
}
