#include <bits/stdc++.h>
using namespace std;

constexpr static int di[4] = {0, 0, -1, +1};
constexpr static int dj[4] = {-1, +1, 0, 0};

inline bool boundCheck(int i, int max_i) {
  return 0 <= i && i < max_i;
}

inline bool boundCheck(int i, int min_i, int max_i) {
  return min_i <= i && i < max_i;
}

inline bool boundCheck2d(int i, int j, int max_i, int max_j) {
  return boundCheck(i, max_i) && boundCheck(j, max_j);
}

inline bool boundCheck2d(int i,
                         int j,
                         int min_i,
                         int min_j,
                         int max_i,
                         int max_j) {
  return boundCheck(i, min_i, max_i) && boundCheck(j, min_j, max_j);
}

struct BridgeCost {
  int src, dst, cost;

  friend bool operator<(const BridgeCost& lhs, const BridgeCost& rhs) {
    return rhs.cost < lhs.cost;
  }
};

struct UnionFindSet {
  UnionFindSet(int size) : root_(size), rank_(size, 0), size_(size, 1) {
    for (int i = 0; i < size; ++i) {
      root_[i] = i;
    }
  }

  int find(int i) {
    if (root_[i] == i) {
      return i;
    }
    int root = find(root_[i]);
    root_[i] = root;
    return root;
  }

  int merge(int i, int j) {
    int i_root = find(i);
    int j_root = find(j);
    if (i_root == j_root) {
      return size_[i_root];
    }
    if (rank_[i_root] < rank_[j_root]) {
      root_[i_root] = j_root;
      size_[j_root] += size_[i_root];
      size_[i_root] = 0;
      return size_[j_root];
    }
    root_[j_root] = i_root;
    size_[i_root] += size_[j_root];
    size_[j_root] = 0;
    if (rank_[i_root] == rank_[j_root]) {
      rank_[i_root]++;
    }
    return size_[i_root];
  }

  bool resize(size_t size) {
    size_t size_before = root_.size();

    if (size_before >= size) {
      return false;
    }
    root_.resize(size);
    rank_.resize(size, 0);
    size_.resize(size, 1);
    for (int i = size_before; i < size; ++i) {
      root_[i] = i;
    }
    return true;
  }

  size_t size() const { return root_.size(); }

  vector<int> root_;
  vector<int> rank_;
  vector<int> size_;
};

class World {
 public:
  World(int R, int C) : R(R), C(C), grid(R, vector<int>(C, 0)) {}

  friend istream& operator>>(istream& istr, World& rhs) {
    for (int i = 0; i < rhs.R; ++i) {
      for (int j = 0; j < rhs.C; ++j) {
        cin >> rhs.grid[i][j];
      }
    }
    return istr;
  }

  int compute() {
    find_islands();
    auto costs = compute_bridge_costs();

    // for (auto [u, v, c] : costs) {
    // printf("%d %d %d\n", u, v, c);
    //}

    int n_islands = island_boundaries.size();
    UnionFindSet ufs(n_islands);
    int total_cost = 0;
    priority_queue<BridgeCost> pq(costs.begin(), costs.end());
    while (!pq.empty()) {
      auto [u, v, cost] = pq.top();
      pq.pop();
      u--;
      v--;
      if (ufs.find(u) == ufs.find(v)) {
        continue;
      }
      ufs.merge(u, v);
      total_cost += cost;
    }
    set<int> ids;
    for (int i = 0; i < n_islands; ++i) {
      ids.insert(ufs.find(i));
    }
    if (ids.size() > 1) {
      return -1;
    }
    return total_cost;
  }

 private:
  void find_islands() {
    vector<vector<bool>> visited(R, vector<bool>(C, false));
    island_ids.clear();
    island_ids.resize(R, vector<int>(C, 0));
    for (int i = 0; i < R; ++i) {
      for (int j = 0; j < C; ++j) {
        if (is_water(i, j) || visited[i][j]) {
          continue;
        }
        island_boundaries.push_back(vector<pair<int, int>>());
        queue<pair<int, int>> Q;
        Q.push({i, j});
        while (!Q.empty()) {
          auto [r, c] = Q.front();
          Q.pop();
          if (visited[r][c]) {
            continue;
          }
          visited[r][c] = true;
          if (is_boundary(r, c)) {
            island_boundaries.back().push_back({r, c});
            island_ids[r][c] = island_boundaries.size();
          }
          for (int k = 0; k < 4; ++k) {
            int rr = r + di[k];
            int cc = c + dj[k];
            if (!is_out(rr, cc) && is_land(rr, cc)) {
              Q.push({rr, cc});
            }
          }
        }
      }
    }
  }

  BridgeCost compute_bridge_cost(int i, int j, int di, int dj) {
    int id = island_ids[i][j];
    int cost = 0;
    while (!is_out(i + di, j + dj) && is_water(i + di, j + dj)) {
      i += di;
      j += dj;
      cost += 1;
    }
    if (is_out(i + di, j + dj)) {
      return {0, 0, 0};
    }
    if (island_ids[i + di][j + dj] == id) {
      return {0, 0, 0};
    }
    if (cost < 2) {
      return {0, 0, 0};
    }
    return {id, island_ids[i + di][j + dj], cost};
  }

  vector<BridgeCost> compute_bridge_costs() {
    vector<BridgeCost> costs;
    for (int island = 0; island < island_boundaries.size(); ++island) {
      for (auto [i, j] : island_boundaries[island]) {
        for (int k = 0; k < 4; ++k) {
          int ii = i + di[k];
          int jj = j + dj[k];
          if (!is_out(ii, jj) && is_water(ii, jj)) {
            auto cost = compute_bridge_cost(i, j, di[k], dj[k]);
            if (cost.cost > 0) {
              costs.push_back(cost);
            }
          }
        }
      }
    }
    return costs;
  }

  bool is_land(int i, int j) { return grid[i][j] == 1; }

  bool is_water(int i, int j) { return grid[i][j] == 0; }

  bool is_out(int i, int j) { return !boundCheck2d(i, j, R, C); }

  bool is_boundary(int i, int j) {
    for (int k = 0; k < 4; ++k) {
      int ii = i + di[k];
      int jj = j + dj[k];
      if (boundCheck2d(ii, jj, R, C) && grid[i][j] == 1 && grid[ii][jj] == 0) {
        return true;
      }
    }
    return false;
  }

  int R, C;
  vector<vector<int>> grid;
  vector<vector<int>> island_ids;
  vector<vector<pair<int, int>>> island_boundaries;
};

int main() {
  int N, M;
  scanf("%d %d", &N, &M);

  World W(N, M);
  cin >> W;

  cout << W.compute() << "\n";

  return 0;
}
