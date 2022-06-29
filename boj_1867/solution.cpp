#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()

using namespace std;
using LL = long long;

class BipartiteMatching {
 public:
  const vector<vector<int>>& edges_;
  size_t nDst_;
  vector<int> matches_;
  vector<bool> visited_;

 public:
  BipartiteMatching(const vector<vector<int>>& edges, int nDst = -1)
      : edges_(edges), nDst_(nDst) {
    if (nDst_ == -1) {
      for (int i = 0; i < edges.size(); ++i) {
        for (int w : edges[i]) {
          nDst_ = max(nDst_, (size_t)(w+1));
        }
      }
    }
    matches_.resize(nDst, -1);
    visited_.resize(nDst, false);
  }

  size_t solve() {
    size_t res = 0;
    for (size_t i = 0; i < edges_.size(); ++i) {
      fill(all(visited_), false);
      res += dfs(i);
    }
    return res;
  }

  std::vector<std::pair<int, int>> matches() const {
    std::vector<std::pair<int, int>> res;
    for (size_t dst = 0; dst < matches_.size(); ++dst) {
      const auto& src = matches_[dst];
      if (src != -1) {
        res.push_back({src, dst});
      }
    }
    return res;
  }

 private:
  bool dfs(int src) {
    for (int dst : edges_[src]) {
      if (visited_[dst]) {
        continue;
      }
      visited_[dst] = true;
      if (matches_[dst] == -1 || dfs(matches_[dst])) {
        matches_[dst] = src;
        return true;
      }
    }
    return false;
  }
};

int main() {
  int N, K;
  scanf("%d %d", &N, &K);

  
  vector<vector<int>> edges(N);
  for (int i = 0; i < K; ++i) {
    int u, v;
    scanf("%d %d", &u, &v);
    u--; v--;
    // (돌맹이의 행 -> 돌맹이의 열) 을 간선으로.
    edges[u].push_back(v);
  }
  
  BipartiteMatching bm(edges, N);
  int ans = bm.solve();
  printf("%d\n", ans);

  return 0;
}
