#include <bits/stdc++.h>
using namespace std;

class BipartiteMatching {
 public:
  const vector<vector<int>>& graph_;
  size_t nDst_;
  vector<int> matches_;

 public:
  BipartiteMatching(const vector<vector<int>>& graph, size_t nDst = 0)
      : graph_(graph), nDst_(nDst), matches_() {
    if (nDst_ == 0) {
      nDst_ = 0;
      for (size_t i = 0; i < graph.size(); ++i) {
        for (size_t w : graph[i]) {
          nDst_ = max(nDst_, (size_t)(w + 1));
        }
      }
    }
    matches_.resize(nDst_, -1);
  }

  size_t solve() {
    size_t res = 0;
    for (size_t i = 0; i < graph_.size(); ++i) {
      vector<bool> visited(nDst_, false);
      res += dfs(i, visited);
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
  bool dfs(int src, vector<bool>& visited) {
    for (int dst : graph_[src]) {
      if (visited[dst]) {
        continue;
      }
      visited[dst] = true;
      if (matches_[dst] == -1 || dfs(matches_[dst], visited)) {
        matches_[dst] = src;
        return true;
      }
    }
    return false;
  }
};

void solve() {
  int N, M;
  scanf("%d %d", &N, &M);

  vector<vector<int>> graph(M);
  for (int i = 0; i < M; ++i) {
    int l, r;
    scanf("%d %d", &l, &r);
    for (int j = l-1; j < r; ++j) {
      graph[i].push_back(j);
    }
  }

  BipartiteMatching bm(graph, N);
  int ans = bm.solve();
  printf("%d\n", ans);
}

int main() {
  int T;
  scanf("%d", &T);
  
  while (T--) {
    solve();
  }

  return 0;
}
