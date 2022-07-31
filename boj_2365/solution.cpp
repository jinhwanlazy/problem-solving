#include <bits/stdc++.h>
using namespace std;

constexpr static int INF = numeric_limits<int>::max();

class Dinic {
 public:
  using flow_t = int;
  constexpr static flow_t INF = numeric_limits<flow_t>::max();

  int N_;
  int src_;
  int sink_;
  vector<vector<flow_t>> cap_;
  vector<vector<flow_t>> flow_;
  vector<set<int>> graph_;

  Dinic(int N)
      : N_(N),
        src_(0),
        sink_(N - 1),
        cap_(vector<vector<flow_t>>(N, vector<flow_t>(N, 0))),
        flow_(vector<vector<flow_t>>(N, vector<flow_t>(N, 0))),
        graph_(vector<set<int>>(N)) {}

  void clear() {
    cap_ = vector<vector<flow_t>>(N_, vector<flow_t>(N_, 0));
    flow_ = vector<vector<flow_t>>(N_, vector<flow_t>(N_, 0));
    graph_ = vector<set<int>>(N_);
  }

  void addEdge(int u, int v, flow_t cap, bool bidirectional=false) {
    cap_[u][v] += cap;
    if (bidirectional) {
      cap_[v][u] += cap;
    }
    graph_[u].insert(v);
    graph_[v].insert(u);
  }

  void setSrcSink(int src, int sink) {
    src_ = src;
    sink_ = sink;
  }

  flow_t solve() {
    flow_t res = 0;
    vector<int> level;
    vector<set<int>::iterator> skipIdx(N_);
    while (buildLevelGraph(level)) {
      for (int i = 0; i < N_; ++i) {
        skipIdx[i] = graph_[i].begin();
      }
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
            vector<set<int>::iterator>& skipIdx) {
    if (u == sink_) {
      return maxFlow;
    }
    for (auto& it = skipIdx[u]; it != graph_[u].end(); ++it) {
      int v = *it;
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

  vector<int> rowSum(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &rowSum[i]);
  }
  
  vector<int> colSum(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &colSum[i]);
  }
  
  int sum = accumulate(rowSum.begin(), rowSum.end(), 0);
  int src = 0;
  int sink = 1;

  Dinic maxFlow(2 * N + 2);
  maxFlow.setSrcSink(src, sink);

  int l = 0, r = 10000;
  while (l + 1 < r) {
    int m = (l + r) / 2;
    maxFlow.clear();
    
    for (int i = 0; i < N; ++i) {
      maxFlow.addEdge(src, 2+i, rowSum[i]);
      maxFlow.addEdge(2+N+i, sink, colSum[i]);
      for (int j = 0; j < N; ++j) {
        maxFlow.addEdge(2+i, 2+N+j, m);
      }
    }
    
    int flow = maxFlow.solve();

    if (sum == flow) {
      r = m;
    }
    else {
      l = m;
    }
  }

  int m = r;
  maxFlow.clear();
  
  for (int i = 0; i < N; ++i) {
    maxFlow.addEdge(src, 2+i, rowSum[i]);
    maxFlow.addEdge(2+N+i, sink, colSum[i]);
    for (int j = 0; j < N; ++j) {
      maxFlow.addEdge(2+i, 2+N+j, m);
    }
  }
  
  maxFlow.solve();
  printf("%d\n", m);
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      printf("%d ", maxFlow.flow_[i+2][j+2+N]);
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
