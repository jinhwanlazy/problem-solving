#include <bits/stdc++.h>
using namespace std;

class BipartiteMatching {
 public:
  BipartiteMatching(uint64_t nSrcNodes, uint64_t nDstNodes)
      : edges_(nSrcNodes, std::vector<bool>(nDstNodes, false)),
        matches_(nDstNodes, -1),
        visited_(nDstNodes, false) {}

  void addEdge(uint64_t src, uint64_t dst) { edges_[src][dst] = true; }

  size_t solve() {
    size_t res = 0;
    for (size_t i = 0; i < edges_.size(); ++i) {
      std::fill(visited_.begin(), visited_.end(), false);
      res += dfs(i);
    }
    return res;
  }

  std::vector<std::pair<uint64_t, uint64_t>> matches() const {
    std::vector<std::pair<uint64_t, uint64_t>> res;
    for (size_t dst = 0; dst < matches_.size(); ++dst) {
      const auto& src = matches_[dst];
      if (src != -1) {
        res.push_back({src, dst});
      }
    }
    return res;
  }

 private:
  bool dfs(uint64_t src) {
    for (size_t dst = 0; dst < edges_[src].size(); ++dst) {
      if (!edges_[src][dst]) {
        continue;
      }
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

 private:
  std::vector<std::vector<bool>> edges_;
  std::vector<uint64_t> matches_;
  std::vector<bool> visited_;
};

int main() {
  int N, M;
  cin >> N >> M;

  BipartiteMatching bm(N, M);
  for (int cow = 0; cow < N; ++cow) {
    int S;
    cin >> S;
    for (int j = 0; j < S; ++j) {
      int cell;
      cin >> cell;
      bm.addEdge(cow, cell - 1);
    }
  }
  cout << bm.solve() << "\n";
}
