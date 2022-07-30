#include <bits/stdc++.h>
using namespace std;

using LL = long long;
constexpr static LL INF = numeric_limits<LL>::max() / 2;

class BellmanFord {
  using cost_t = LL;

 public:
  struct Edge {
    int u;
    int v;
    cost_t c;
  };

  int nVertices_;
  int src_;
  vector<Edge> edges_;
  vector<cost_t> costs_ = {};

  BellmanFord(int nVertices, int src = 0, const vector<Edge>& edges = {})
      : nVertices_(nVertices), src_(src), edges_(edges) {}

  void setSrc(int src) { src_ = src; }
  void setNVertices(int nVertices) { nVertices_ = nVertices; }
  void addEdge(int u, int v, cost_t c) { edges_.emplace_back(u, v, c); }

  bool solve() {
    costs_.resize(nVertices_);
    fill(costs_.begin(), costs_.end(), INF);
    costs_[src_] = 0;

    for (int i = 0; i < nVertices_; ++i) {
      for (const auto& [u, v, c] : edges_) {
        if (costs_[u] != INF && costs_[v] > costs_[u] + c) {
          costs_[v] = costs_[u] + c;
          if (i == nVertices_ - 1) {
            return false;
          }
        }
      }
    }
    return true;
  }
};

class SPFA {
  using cost_t = LL;

 public:
  struct Edge {
    int dst;
    cost_t cost;
  };

  int nVertices_;
  int src_;
  vector<vector<Edge>> graph_;
  vector<cost_t> costs_ = {};

  SPFA(int nVertices, int src = 0, const vector<vector<Edge>>& graph = {})
      : nVertices_(nVertices), src_(src), graph_(graph) {
    if (graph_.empty()) {
      graph_.resize(nVertices);
    }
  }

  void setSrc(int src) { src_ = src; }
  void setNVertices(int nVertices) { nVertices_ = nVertices; }
  void addEdge(int u, int v, cost_t c) { graph_[u].emplace_back(v, c); }

  bool solve() {
    costs_.resize(nVertices_);
    fill(costs_.begin(), costs_.end(), INF);
    costs_[src_] = 0;

    vector<int> cycle(nVertices_, 0);
    cycle[src_]++;

    queue<int> Q;
    Q.push(src_);

    vector<bool> inQ(nVertices_, false);
    inQ[src_] = true;

    while (!Q.empty()) {
      int u = Q.front();
      Q.pop();
      inQ[u] = false;

      for (const auto& [v, c] : graph_[u]) {
        if (costs_[u] != INF && costs_[v] > costs_[u] + c) {
          costs_[v] = costs_[u] + c;
          if (!inQ[v]) {
            cycle[v]++;
            if (cycle[v] > nVertices_) {
              return false;
            }
            Q.push(v);
            inQ[v] = true;
          }
        }
      }
    }
    return true;
  }
};


int main() {
  int N, M;
  scanf("%d %d", &N, &M);

  //BellmanFord bm(N, 0);
  SPFA spfa(N, 0);
  for (int i = 0; i < M; ++i) {
    int u, v, c;
    scanf("%d %d %d", &u, &v, &c);
    u--; v--;
    spfa.addEdge(u, v, c);
  }

  if (!spfa.solve()) {
    printf("%d\n", -1);
  } else {
    for (int i = 1; i < N; ++i) {
      printf("%lld\n", spfa.costs_[i] == INF ? -1 : spfa.costs_[i]);
    }
  }

  return 0;
}
