#include <bits/stdc++.h>
using namespace std;

void dfs(const vector<vector<int>>& edges, vector<bool>& visited, vector<int>& trace, int u) {
  static int count = 1;
  visited[u] = true;
  trace[u] = count++;
  for (int v : edges[u]) {
    if (!visited[v]) {
      dfs(edges, visited, trace, v);
    }
  }
}

void bfs(const vector<vector<int>>& edges, vector<bool>& visited, vector<int>& trace, int u) {
  visited[u] = true;
  static int count = 1;
  queue<int> Q;
  Q.push(u);
  while (!Q.empty()) {
    u = Q.front(); Q.pop();
    trace[u] = count++;
    for (int v : edges[u]) {
      if (!visited[v]) {
        visited[v] = true;
        Q.push(v);
      }
    }
  }
  
}

int main() {
  int N, M, R;
  scanf("%d %d %d", &N, &M, &R);
  
  vector<vector<int>> edges(N);
  vector<bool> visited(N, false);
  for (int i = 0; i < M; ++i) {
    int u, v;
    scanf("%d %d", &u, &v);
    u--;
    v--;
    edges[u].push_back(v);
    edges[v].push_back(u);
  }

  for (auto& vs : edges) {
    sort(vs.begin(), vs.end(), [](int l, int r) -> bool { return l > r; });
    //sort(vs.begin(), vs.end());
  }

  vector<int> trace(N, 0);

  bfs(edges, visited, trace, R-1);
  for (int t : trace) {
    printf("%d\n", t);
  }
  return 0;
}



