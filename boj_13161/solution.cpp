#include <bits/stdc++.h>
#include <limits>
using namespace std;

class Dinic {
 public:
  using flow_t = int;
  constexpr static flow_t INF = numeric_limits<flow_t>::max();

  int N_;
  int src_;
  int sink_;
  vector<vector<flow_t>> cap_;
  vector<vector<flow_t>> flow_;
  vector<vector<int>> graph_;

  Dinic(int N)
      : N_(N),
        src_(0),
        sink_(N - 1),
        cap_(vector<vector<flow_t>>(N, vector<flow_t>(N, 0))),
        flow_(vector<vector<flow_t>>(N, vector<flow_t>(N, 0))),
        graph_(vector<vector<int>>(N)) {}

  void addEdge(int u, int v, flow_t cap, bool bidirectional = false) {
    cap_[u][v] += cap;
    if (bidirectional) {
      cap_[v][u] += cap;
    }
    graph_[u].push_back(v);
    graph_[v].push_back(u);
  }

  void setSrcSink(int src, int sink) {
    src_ = src;
    sink_ = sink;
  }

  flow_t solve() {
    flow_t res = 0;
    vector<int> level;
    vector<size_t> skipIdx(N_);
    while (buildLevelGraph(level)) {
      fill(skipIdx.begin(), skipIdx.end(), 0);
      while (flow_t f = letFlow(src_, INF, level, skipIdx)) {
        res += f;
      }
    }
    return res;
  }

 private:
  bool buildLevelGraph(vector<int>& level) const {
    level.resize(N_);
    fill(level.begin(), level.end(), -1);
    level[src_] = 0;

    queue<int> Q;
    Q.push(src_);
    while (!Q.empty()) {
      int u = Q.front();
      Q.pop();
      for (int v : graph_[u]) {
        if (level[v] == -1 && cap_[u][v] - flow_[u][v] > 0) {
          level[v] = level[u] + 1;
          Q.push(v);
        }
      }
    }
    return level[sink_] != -1;
  }

  flow_t letFlow(int u,
                 int maxFlow,
                 const vector<int>& level,
                 vector<size_t>& skipIdx) {
    if (u == sink_) {
      return maxFlow;
    }
    for (auto& i = skipIdx[u]; i < graph_[u].size(); ++i) {
      int v = graph_[u][i];
      flow_t cap = cap_[u][v] - flow_[u][v];
      if (level[u] + 1 == level[v] && cap > 0) {
        flow_t f = letFlow(v, min(maxFlow, cap), level, skipIdx);
        if (f > 0) {
          flow_[u][v] += f;
          flow_[v][u] -= f;
          return f;
        }
      }
    }
    return 0;
  }
};

void solve() {
  int N;
  scanf("%d", &N);

  vector<int> AB(N + 1);
  for (int i = 1; i <= N; ++i) {
    scanf("%d", &AB[i]);
  }

  int ans = 0;
  Dinic dinic(N + 2);
  for (int i = 1; i <= N; ++i) {
    if (AB[i] == 1) {
      // src -> groupA
      dinic.addEdge(0, i, Dinic::INF, true);
    }
    if (AB[i] == 2) {
      // groupB -> sink
      dinic.addEdge(i, N + 1, Dinic::INF, true);
    }

    for (int j = 1; j <= N; ++j) {
      int sadness;
      scanf("%d", &sadness);
      if (i <= j)
        continue;
      if ((AB[i] == 1 && AB[j] == 2) or (AB[i] == 2 && AB[j] == 1)) {
        ans += sadness;
      } else {
        dinic.addEdge(i, j, sadness, true);
      }
    }
  }

  ans += dinic.solve();
  printf("%d\n", ans);

  vector<bool> visited(dinic.N_, false);
  queue<int> Q;
  Q.push(0);
  while (!Q.empty()) {
    int u = Q.front(); Q.pop();
    if (visited[u]) continue;
    visited[u] = true;
    for (int v : dinic.graph_[u]) {
      if (!visited[v] && dinic.cap_[u][v] - dinic.flow_[u][v] > 0) {
        Q.push(v);
      }
    }
  }

  for (int i = 1; i <= N; ++i) {
    if (visited[i]) {
      printf("%d ", i);
    }
  }
  printf("\n");
  
  for (int i = 1; i <= N; ++i) {
    if (!visited[i]) {
      printf("%d ", i);
    }
  }
  printf("\n");
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
