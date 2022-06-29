#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()

using namespace std;
using LL = long long;

constexpr static int di[6] = {0, 0, -1, -1, +1, +1};
constexpr static int dj[6] = {-1, +1, -1, +1, -1, +1};

inline bool boundCheck(int i, int max_i) {
  return 0 <= i && i < max_i;
}

inline bool boundCheck2d(int i, int j, int max_i, int max_j) {
  return boundCheck(i, max_i) && boundCheck(j, max_j);
}

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

void solve() {
  int N, M;
  scanf("%d %d", &N, &M);
  
  int totalSeats = 0;
  vector<vector<char>> seats(N, vector<char>(M, ' '));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      scanf(" %c", &seats[i][j]);
      totalSeats += seats[i][j] == '.';
    }
  }

  map<pair<int, int>, int> oddIds, evenIds;
  const auto getSeatId = [&oddIds, &evenIds](int i, int j)->int {
    auto& ids = (j & 1) ? oddIds : evenIds;
    auto it = ids.find({i, j});
    if (it != ids.end()) {
      return it->second;
    }
    int id = ids.size();
    ids[make_pair(i, j)] = id;
    return id;
  };

  vector<vector<int>> edges(N*M);
  
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; j+=2) {
      const char& seat = seats[i][j];
      if (seat == 'x') {
        continue;
      }
      int seatId1 = getSeatId(i, j);
      for (int k = 0; k < 6; ++k) {
        const int ii = i + di[k];
        const int jj = j + dj[k];
        if (!boundCheck2d(ii, jj, N, M)) {
          continue;
        }
        const char& seat2 = seats[ii][jj];
        if (seat2 == 'x') {
          continue;
        }
        int seatId2 = getSeatId(ii, jj);
        edges[seatId1].push_back(seatId2);
      }
    }
  }

  BipartiteMatching bm(edges, oddIds.size());
  int ans = totalSeats - bm.solve();
  printf("%d\n", ans);
}

int main() {
  int C;
  scanf("%d", &C);

  while (C--) {
    solve();
  }
  return 0;
}
