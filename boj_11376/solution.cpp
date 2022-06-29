#include <bits/stdc++.h>
#include <ratio>
#define all(x) (x).begin(), (x).end()

using namespace std;

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
  int N, M;
  scanf("%d %d", &N, &M);

  vector<vector<int>> edges(N);
  for (int i = 0; i < N; ++i)  {
    int nWork;
    scanf("%d", &nWork);
    edges[i].reserve(nWork);
    for (int j = 0; j < nWork; ++j) {
      int w;
      scanf("%d", &w);
      edges[i].push_back(w-1);
    }
  }

  BipartiteMatching bm(edges, M);
  int ans = bm.solve();
  printf("%d\n", ans);
  return 0;
}
