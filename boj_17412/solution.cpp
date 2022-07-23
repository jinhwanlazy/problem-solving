#include <bits/stdc++.h>
#include <cmath>
#include <limits>
#define all(x) (x).begin(), (x).end()

using namespace std;
using LL = long long;

class MaxFlow {
 public:
  int N_;
  vector<vector<int>> cap_;
  vector<vector<int>> flow_;
  vector<list<int>> graph_;

  int src_;
  int sink_;

  MaxFlow(int N)
      : N_(N),
        cap_(vector<vector<int>>(N, vector<int>(N, 0))),
        flow_(vector<vector<int>>(N, vector<int>(N, 0))),
        graph_(vector<list<int>>(N)) {}

  void setEdge(int u, int v, int cap) {
    cap_[u][v] = cap;
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
      int flow = numeric_limits<int>::max();
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

 private:
  vector<int> findPath() {
    queue<int> Q;
    vector<int> trace(N_, -1);
    Q.push(src_);
    while (!Q.empty()) {
      int u = Q.front(); Q.pop();
      for (int v : graph_[u]) {
        if (flow_[u][v] < cap_[u][v] && trace[v]==-1) {
          trace[v] = u;
          Q.push(v);
          if (v == sink_) {
            return trace;
          }
        }
      }       
    }
    return trace;
  }
};

int main() {
  int N, P;
  scanf("%d %d", &N, &P);

  MaxFlow mf(N);
  for (int i = 0; i < P; ++i) {
    int u, v;
    scanf("%d %d", &u, &v);
    u--; v--;
    mf.setEdge(u, v, 1);
  }
  mf.setSrcSink(0, 1);
  int ans = mf.solve();
  printf("%d\n", ans);
  return 0;
}
