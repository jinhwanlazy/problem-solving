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

int main() {
  int N, M;
  scanf("%d %d", &N, &M);
  
  vector<vector<int>> graph(N);
  for (int i = 0; i < M; ++i) {
    int u, v;
    scanf("%d %d", &u, &v);
    u--;
    v--;
    graph[u].push_back(v);
  }

  auto res = topologicalSort(graph);

  for (int i = 0; i < res.size(); ++i) {
    printf("%d ", res[i]+1);
  }
  printf("\n");

  return 0;
}

