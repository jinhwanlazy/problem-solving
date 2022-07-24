#include <bits/stdc++.h>
using namespace std;

class Dijkstra {
 public:
  using cost_t = int;
  static constexpr cost_t INF = numeric_limits<cost_t>::max();

  struct State {
    int u;
    cost_t cost;

    friend bool operator<(const State& lhs, const State& rhs) { return lhs.cost > rhs.cost; }
  };

  struct Edge {
    int u;
    int v;
    cost_t cost;
  };

 public:
  const vector<vector<Edge>>& graph_;
  vector<cost_t> costs_;
  vector<int> trace_;

  int src_;
  int dst_ = -1;
  bool doTrace_ = false;

 public:
  Dijkstra(const vector<vector<Edge>>& adjListGraph, int src)
      : graph_(adjListGraph), costs_(adjListGraph.size()), trace_(0), src_(src) {}

  void setDoTrace() { doTrace_ = true; }
  void setSrc(int src) { src_ = src; }
  void setDst(int dst) { dst_ = dst; }
  const vector<cost_t>& cost() const { return costs_; }
  const vector<int>& trace() const { return trace_; }

  void solve() {
    if (src_ == -1) {
      throw runtime_error("src is not defined!");
    }
    fill(costs_.begin(), costs_.end(), INF);
    if (doTrace_) {
      trace_.resize(costs_.size());
      fill(trace_.begin(), trace_.end(), -1);
    }

    priority_queue<State> pq;
    costs_[src_] = 0;
    pq.push({src_, 0});
    while (!pq.empty()) {
      auto [u, c] = pq.top();
      pq.pop();
      if (costs_[u] < c) {
        continue;
      }
      if (u == dst_) {
        break;
      }
      for (const auto& [_, v, w] : graph_[u]) {
        cost_t nextCost = c + w;
        if (nextCost < costs_[v]) {
          costs_[v] = nextCost;
          pq.push({v, nextCost});
          if (doTrace_) {
            trace_[v] = u;
          }
        }
      }
    }
  }
};


int main() {
  int V, E;
  scanf("%d %d", &V, &E);

  int K;
  scanf("%d", &K);
  K--;

  vector<vector<Dijkstra::Edge>> graph(V);
  for (int i = 0; i < E; ++i) {
    int u, v, w;
    scanf("%d %d %d", &u, &v, &w);
    u--; v--;
    graph[u].push_back({u, v, w});
  }
  
  Dijkstra s(graph, K);
  s.solve();
  for (auto c : s.cost()) {
    if (c != Dijkstra::INF) {
      printf("%d\n", c);
    } else {
      printf("INF\n");
    }
  }
  return 0;
}
