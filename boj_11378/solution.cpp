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

  size_t solve(int K) {
    size_t res = 0;
    for (size_t i = 0; i < edges_.size(); ++i) {
      fill(all(visited_), false);
      res += dfs(i);
    }
    for (size_t i = 0; i < edges_.size() && K > 0; ++i) {
      fill(all(visited_), false);
      while (K > 0 && dfs(i)) {
        res += 1;
        K--;
      }
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
  int N, M, K;
  scanf("%d %d %d", &N, &M, &K);

  vector<vector<int>> edges(N);
  for (int i = 0; i < N; ++i) {
    int nAvail;
    scanf("%d", &nAvail);
    for (int j = 0; j < nAvail; ++j) {
      int w;
      scanf("%d", &w);
      w--;
      edges[i].push_back(w);
    }
  }

  BipartiteMatching bm(edges, M);
  int ans = bm.solve(K);
  printf("%d\n", ans);

  return 0;
}
