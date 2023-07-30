#include <bits/stdc++.h>
using namespace std;

vector<int> topologicalSort(const vector<vector<int>>& graph) {
  size_t N = graph.size();
  vector<int> incomming(N, 0);
  for (int u = 0; u < graph.size(); ++u) {
    for (int v : graph[u]) {
      incomming[v]++;
    }
  }

  queue<int> Q;
  for (int v = 0; v < N; ++v) {
    if (incomming[v] == 0) {
      Q.push(v);
    }
  }

  vector<int> res;
  while (!Q.empty()) {
    int u = Q.front(); Q.pop();
    res.push_back(u);
    for (int v : graph[u]) {
      incomming[v]--;
      if (incomming[v] == 0) {
        Q.push(v);
      }
    }
  }
  return res;
}

void solve() {
  int N;
  scanf("%d", &N);

  vector<vector<int>> graph(N);
  vector<vector<int>> graph_inv(N);
  vector<int> times(N);

  for (int i = 0; i < N; ++i) {
    int t;
    scanf("%d", &t);
    times[i] = t;
    
    vector<int> parents;
    while (true) {
      int j;
      scanf("%d", &j);
      if (j == -1) {
        break;
      }
      --j;
      graph[j].push_back(i);
      graph_inv[i].push_back(j);
    }
  }

  auto order = topologicalSort(graph);

  vector<int> res(N);
  for (int i : order) {
    int max_t = 0;
    for (int j : graph_inv[i]) {
      max_t = max(max_t, res[j]);
    }
    res[i] = max_t + times[i];
  }
  for (int i = 0; i < N; ++i) {
    printf("%d\n", res[i]);
  }
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
