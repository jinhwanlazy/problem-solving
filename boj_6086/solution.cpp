#include <bits/stdc++.h>
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
  vector<set<int>> graph_;

  Dinic(int N)
      : N_(N),
        src_(0),
        sink_(N - 1),
        cap_(vector<vector<flow_t>>(N, vector<flow_t>(N, 0))),
        flow_(vector<vector<flow_t>>(N, vector<flow_t>(N, 0))),
        graph_(vector<set<int>>(N)) {}

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

int char2int(char c) {
  if (c >= 'a') {
    return c - 'a' + 26;
  }
  return c - 'A';
}

void solve() {
  int N;
  scanf("%d", &N);

  Dinic mf(26 * 2);
  mf.setSrcSink(0, 25);
  for (int i = 0; i < N; ++i) {
    char u, v;
    int f;
    scanf(" %c %c %d", &u, &v, &f);
    u = char2int(u);
    v = char2int(v);
    mf.addEdge(u, v, f, true);
  }

  auto ans = mf.solve();
  printf("%d\n", ans);
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
