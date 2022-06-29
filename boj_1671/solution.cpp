#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()

using namespace std;
using LL = long long;

struct Shark {
  int a, b, c;
  
  bool operator==(const Shark& other) {
    return a == other.a && b == other.b && c == other.c;
  }

  friend bool operator<=(const Shark& lhs, const Shark& rhs) {
    return lhs.a <= rhs.a && lhs.b <= rhs.b && lhs.c <= rhs.c;
  }
};

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
  int N;
  scanf("%d", &N);

  vector<Shark> sharks(N);
  for (int i = 0; i < N; ++i) {
    auto& s = sharks[i];
    scanf("%d %d %d", &s.a, &s.b, &s.c);
  }

  vector<vector<int>> edges(N);
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      if (i == j) {
        continue;
      }
      if (sharks[i] == sharks[j]) {
        if (i < j) {
          edges[j].push_back(i);
        }
      }
      else if (sharks[i] <= sharks[j]) {
        edges[j].push_back(i);
      }
    }
  }

  BipartiteMatching bm(edges, N);
  int ans =  N - bm.solve();
  printf("%d\n", ans);
  

  return 0;
}
