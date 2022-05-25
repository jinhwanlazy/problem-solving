#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, M;
  scanf("%d %d", &N, &M);

  map<int, int> jumps;
  for (int i = 0; i < N; ++i) {
    int u, v;
    scanf("%d %d", &u, &v);
    u--;
    v--;
    jumps[u] = v;
  }
  for (int i = 0; i < M; ++i) {
    int u, v;
    scanf("%d %d", &u, &v);
    u--;
    v--;
    jumps[u] = v;
  }

  vector<vector<int>> edges(100);
  for (int u = 0; u < 100; ++u) {
    for (int v = u+1; v <= u+6 && v < 100; ++v) {
      if (jumps.find(v) == jumps.end()) {
        edges[u].push_back(v);
      }
      else {
        edges[u].push_back(jumps[v]);
      }
    }
  }

  vector<bool> visited(100, false);
  queue<pair<int, int>> Q;
  visited[0] = true;
  Q.push({0, 0});
  while (!Q.empty()) {
    auto [u, count] = Q.front(); Q.pop();
    if (u == 99) {
      printf("%d\n", count);
      break;
    }
    for (int v : edges[u]) {
      if (!visited[v]) {
        visited[v] = true;
        Q.push({v, count+1});
      }
    }
  }
  
  return 0;
}
