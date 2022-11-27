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
  Dijkstra(const vector<vector<Edge>>& adjListGraph, int src=0)
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

struct City {
  int s, x, y;
};


void solve() {
  int N, T;
  scanf("%d %d", &N, &T);

  auto getDistance = [T](const City& c1, const City& c2) -> int {
    int res = abs(c1.x - c2.x) + abs(c1.y - c2.y);
    if (c1.s == 1 && c2.s == 1) {
      res = min(res, T);
    }
    return res;
  };

  vector<City> cities(N);
  vector<vector<Dijkstra::Edge>> graph(N);
  for (int i = 0; i < N; ++i) {
    auto& [s, x, y] = cities[i];
    scanf("%d %d %d", &s, &x, &y);
  }
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      if (i != j) {
        graph[i].emplace_back(i, j, getDistance(cities[i], cities[j]));
      }
    }
  }

  Dijkstra dijk(graph);

  int M;
  scanf("%d", &M);
  while (M--) {
    int i, j;
    scanf("%d %d", &i, &j);
    i--; j--;
    dijk.setSrc(i);
    dijk.setDst(j);
    dijk.solve();
    printf("%d\n", dijk.cost()[j]);
  }

}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
