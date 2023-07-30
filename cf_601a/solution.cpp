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
  Dijkstra(const vector<vector<Edge>>& adjListGraph, int src = 0)
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

void solve() {
  int N, M;
  scanf("%d %d", &N, &M);

  set<pair<int, int>> rails_set;
  vector<vector<Dijkstra::Edge>> rails(N), roads(N);
  for (int i = 0; i < M; ++i) {
    int u, v;
    scanf("%d %d", &u, &v);
    --u; --v;
    rails_set.insert({u, v});
    rails_set.insert({v, u});
    rails[u].push_back({u, v, 1});
    rails[v].push_back({v, u, 1});
  }
  for (int i = 0; i + 1 < N; ++i) {
    for (int j = i + 1; j < N; ++j) {
      if (rails_set.find({i, j}) == rails_set.end()) {
        roads[i].push_back({i, j, 1});
        roads[j].push_back({j, i, 1});
      }
    }
  }

  Dijkstra rail_path(rails);
  rail_path.setSrc(0);
  rail_path.setDst(N-1);
  rail_path.solve();

  Dijkstra road_path(roads);
  road_path.setSrc(0);
  road_path.setDst(N-1);
  road_path.solve();

  int rail_cost = rail_path.cost()[N-1];
  int road_cost = road_path.cost()[N-1];

  if (rail_cost == Dijkstra::INF || road_cost == Dijkstra::INF) {
    printf("%d\n", -1);
  } else {
    printf("%d\n", max(rail_cost, road_cost));
  }
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
