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
  int N, M;
  scanf("%d %d", &N, &M);

  vector<vector<int>> graph(N);
  for (int i = 0; i < M; ++i) {
    int K;
    scanf("%d", &K);
    vector<int> xs(K);
    for (int i = 0; i < K; ++i) {
      scanf("%d", &xs[i]);
      xs[i]--;
    }
    for (int k = 0; k < K-1; ++k) {
      graph[xs[k]].push_back(xs[k+1]);
    }
  }

  auto res = topologicalSort(graph);
  if (res.size() != N) {
    printf("%d\n", 0);
  }
  else {
    for (int i = 0; i < res.size(); ++i) {
      printf("%d\n", res[i]+1);
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
