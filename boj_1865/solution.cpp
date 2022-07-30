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

 private:
  int nVertices_;
  int src_;
  vector<Edge> edges_;
  vector<cost_t> costs_ = {};

 public:
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

void solve() {
  int N, M, W;
  scanf("%d %d %d", &N, &M, &W);

  BellmanFord bm(N, 0);
  for (int i = 0; i < M; ++i) {
    int u, v, c;
    scanf("%d %d %d", &u, &v, &c);
    u--;
    v--;
    bm.addEdge(u, v, c);
    bm.addEdge(v, u, c);
  }

  for (int i = 0; i < W; ++i) {
    int u, v, c;
    scanf("%d %d %d", &u, &v, &c);
    u--;
    v--;
    bm.addEdge(u, v, -c);
  }

  if (bm.solve()) {
    printf("NO\n");
  } else {
    printf("YES\n");
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
