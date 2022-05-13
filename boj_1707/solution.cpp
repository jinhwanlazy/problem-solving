#include <bits/stdc++.h>
using namespace std;

bool solution() {
  int V, E;
  scanf("%d %d", &V, &E);

  vector<vector<int>> edges(V + 1);
  for (int i = 0; i < E; ++i) {
    int s, d;
    scanf("%d %d", &s, &d);
    edges[s].push_back(d);
    edges[d].push_back(s);
  }

  vector<int> visited(V + 1, false);
  vector<int> side(V + 1, 0);
  for (int seed = 1; seed <= V; ++seed) {
    if (visited[seed]) {
      continue;
    }
    queue<pair<int, int>> Q;
    Q.push({seed, 0});
    while (!Q.empty()) {
      int u = Q.front().first;
      int s = Q.front().second;
      Q.pop();
      if (visited[u]) {
        if (side[u] != s) {
          return false;
        }
        continue;
      }
      visited[u] = true;
      side[u] = s;
      for (int v : edges[u]) {
        if (!visited[v]) {
          Q.push({v, s ^ 1});
        }
      }
    }
  }
  return true;
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    printf(solution() ? "YES\n" : "NO\n");
  }
  return 0;
}
