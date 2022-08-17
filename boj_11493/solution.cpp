#include <bits/stdc++.h>
using namespace std;

class MCMF {
 public:
  using flow_t = int;
  using cost_t = int;

  int N_;
  int src_;
  int sink_;
  vector<vector<flow_t>> cap_;
  vector<vector<flow_t>> flow_;
  vector<vector<cost_t>> cost_;
  vector<vector<int>> graph_;

  MCMF(int N)
      : N_(N),
        src_(0),
        sink_(N-1),
        cap_(vector<vector<int>>(N, vector<int>(N, 0))),
        flow_(vector<vector<int>>(N, vector<int>(N, 0))),
        cost_(vector<vector<int>>(N, vector<int>(N, 0))),
        graph_(vector<vector<int>>(N)) {}

  void addEdge(int u, int v, flow_t cap, cost_t cost=1) {
    cap_[u][v] = cap;
    cost_[u][v] = cost;
    cost_[v][u] = -cost;
    
    graph_[u].push_back(v);
    graph_[v].push_back(u);
  }

  void setSrcSink(int src, int sink) {
    src_ = src;
    sink_ = sink;
  }
  
  int solve() {
    int res = 0;
    while (true) {
      vector<int> trace = findPath();
      if (trace[sink_] == -1) {
        break;
      }
      int flow = numeric_limits<flow_t>::max();
      for (int v = sink_; v != src_; v = trace[v]) {
        int u = trace[v];
        flow = min(flow, cap_[u][v] - flow_[u][v]);
      }
      for (int v = sink_; v != src_; v = trace[v]) {
        int u = trace[v];
        flow_[u][v] += flow;
        flow_[v][u] -= flow;
      }
      res += flow;
    }
    return res;
  }

  cost_t totalCost() const {
    cost_t res = 0;
    for (int u = 0; u < N_; ++u) {
      for (int v : graph_[u]) {
        if (v > u) {
          res += cost_[u][v] * flow_[u][v];
        }
      }
    }
    return res;
  }

 private:
  vector<int> findPath() {
    // SPFA algorithm without cycle checking
    vector<int> trace(N_, -1);
    vector<cost_t> costs(N_, numeric_limits<cost_t>::max());
    costs[src_] = 0;
    
    queue<int> Q;
    Q.push(src_);

    vector<bool> inQ(N_, false);
    inQ[src_] = true;

    while (!Q.empty()) {
      int u = Q.front();
      Q.pop();
      inQ[u] = false;

      for (int v : graph_[u]) {
        int c = cost_[u][v];
        if (cap_[u][v] - flow_[u][v] > 0 && costs[v] > costs[u] + c) {
          costs[v] = costs[u] + c;
          trace[v] = u;
          if (!inQ[v]) {
            Q.push(v);
            inQ[v] = true;
          }
        }
      }
    }
    return trace;
  }
};

void solve() {
  int N, M;
  scanf("%d %d", &N, &M);

  MCMF mcmf(N+2);

  for (int i = 0; i < M; ++i) {

  }


  

}

int main() {
  int T;
  scanf("%d", &T);
  
  while (T--) {
    solve();
  }

  return 0;
}
