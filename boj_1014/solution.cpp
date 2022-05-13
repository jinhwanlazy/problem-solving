#include <bits/stdc++.h>
using namespace std;

class BipartiteMatching {
 public:
  BipartiteMatching(uint64_t nSrcNodes, uint64_t nDstNodes)
      : edges_(nSrcNodes, std::vector<bool>(nDstNodes, 0)),
        matches_(nDstNodes, -1),
        visited_(nSrcNodes, false) {}

  void addEdge(uint64_t src, uint64_t dst) { edges_[src][dst] = 1; }

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
    if (visited_[src]) {
      return false;
    }
    visited_[src] = true;
    for (size_t dst = 0; dst < edges_[src].size(); ++dst) {
      if (!edges_[src][dst]) {
        continue;
      }
      if (matches_[dst] >= edges_.size() || dfs(matches_[dst])) {
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

void solve() {
  static constexpr int DX[] = {-1, -1, +1, +1};
  static constexpr int DY[] = {+0, -1, +0, -1};

  int N, M;
  cin >> N >> M;
  vector<string> seats(N);
  for (int i = 0; i < N; ++i) {
    cin >> seats[i];
  }

  BipartiteMatching bm(N * M, N * M);
  int numAvailableSeats = 0;

  for (size_t row = 0; row < seats.size(); ++row) {
    for (size_t col = 0; col < seats[row].size(); ++col) {
      if (seats[row][col] != '.') {
        continue;
      }
      numAvailableSeats++;
      for (size_t i = 0; i < 6; ++i) {
        size_t neighbor_row = row + DY[i];
        size_t neighbor_col = col + DX[i];
        if (neighbor_row >= seats.size() || neighbor_col >= seats[row].size() ||
            seats[neighbor_row][neighbor_col] != '.') {
          continue;
        }
        uint64_t srcIdx = M * row + col;
        uint64_t dstIdx = M * neighbor_row + neighbor_col;
        //
        if (col % 2 == 0) {
          bm.addEdge(srcIdx, dstIdx);
        } else {
          bm.addEdge(dstIdx, srcIdx);
        }
      }
    }
  }
  cout << numAvailableSeats - bm.solve() << "\n";
}

int main() {
  int T;
  cin >> T;
  while (T--) {
    solve();
  }
}
