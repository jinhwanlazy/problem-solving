#include <bits/stdc++.h>
#include <cstdio>
using namespace std;

vector<int> topologicalSort(const vector<set<int>>& graph) {
  size_t N = graph.size();
  vector<int> incomming(N, 0);
  for (int u = 0; u < graph.size(); ++u) {
    for (int v : graph[u]) {
      incomming[v]++;
    }
  }

  priority_queue<int> Q;
  for (int v = 0; v < N; ++v) {
    if (incomming[v] == 0) {
      Q.push(-v);
    }
  }

  vector<int> res;
  while (!Q.empty()) {
    int u = -Q.top(); Q.pop();
    res.push_back(u);
    for (int v : graph[u]) {
      incomming[v]--;
      if (incomming[v] == 0) {
        Q.push(-v);
      }
    }
  }
  return res;
}

void solution() {
  int N;
  scanf("%d", &N);
  

  vector<int> ranking(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &ranking[i]);
    ranking[i]--;
  }
   

  vector<set<int>> graph(N);
  for (int i = 0; i < N-1; ++i) {
    for (int j = i+1; j < N; ++j) {
      graph[ranking[i]].insert(ranking[j]);
    }
  }

  bool mismatch = false;
  int M;
  scanf("%d", &M);
  for (int i = 0; i < M; ++i) {
    int u, v;
    scanf("%d %d", &u, &v);
    u--;
    v--;
    if (graph[u].count(v) == 1) {
      graph[u].erase(v);
      graph[v].insert(u);
    }
    else if (graph[v].count(u) == 1) {
      graph[v].erase(u);
      graph[u].insert(v);
    }
    else {
      mismatch = true;
    }
  }
  if (mismatch) {
    printf("?\n");
    return;
  }

  auto res = topologicalSort(graph);
  if (res.size() != N) {
    printf("IMPOSSIBLE\n");
    return;
  }
  for (int i = 0; i < res.size(); ++i) {
    printf("%d ", res[i]+1);
  }
  printf("\n");
}


int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    solution();
  }
  return 0;
}
