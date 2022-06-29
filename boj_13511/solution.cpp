#include <bits/stdc++.h>
using namespace std;

struct Edge
{
  int u;
  int v;
  int w; /* cost */

  friend bool operator< (const Edge& lhs, const Edge& rhs) {
    return lhs.w > rhs.w;
  }
};

template <bool buildParent = true,
          bool buildChildren = true,
          bool buildDepth = true,
          bool buildCost = true>
class TreeBuilder {
 public:
  size_t N;
  vector<int> parent;
  vector<vector<int>> children;
  vector<int> depth;
  vector<int> cost;
  
  static TreeBuilder build(const vector<vector<Edge>>& biEdges, size_t root) {
    TreeBuilder tree;
    tree.N = biEdges.size();
    vector<bool> visited(tree.N, false);
    if constexpr (buildParent) {
      tree.parent.resize(tree.N, root);
    }
    if constexpr (buildDepth) {
      tree.depth.resize(tree.N, 0);
    }
    stack<pair<size_t, size_t>> S;
    S.push({root, 0});
    while (!S.empty()) {
      auto [u, d] = S.top(); S.pop();
      visited[u] = true;
      for (auto& [u, v, w] : biEdges[u]) {
        if (visited[v]) {
          continue;
        }
        if constexpr (buildChildren) {
          tree.children[u].push_back(v);
        }
        if constexpr (buildParent) {
          tree.parent[v] = u;
        }
        if constexpr (buildCost) {
          tree.cost[v] = w;
        }
        if constexpr (buildDepth) {
          tree.depth[v] = d+1;
        }
        S.push({v, d+1});
      }
    }
    return tree;
  }
};

class SparseTable {
 public:
  vector<vector<int>> jumpTable_;
  vector<vector<int>> costTable_;
  int maxDepth_;

 public:
  SparseTable(const vector<int>& parent, const vector<int>& cost, int maxDepth = 20)
      : jumpTable_(maxDepth), costTable_(maxDepth), maxDepth_(maxDepth) {
    jumpTable_[0] = parent;
    costTable_[0] = cost;
    for (int i = 1; i < maxDepth; ++i) {
      const vector<int>& prev = jumpTable_[i - 1];
      const vector<int>& prevCost = costTable_[i - 1];
      vector<int>& jumpRow = jumpTable_[i];
      vector<int>& costRow = costTable_[i];
      jumpRow.resize(prev.size());
      costRow.resize(prev.size());
      for (int j = 0; j < prev.size(); ++j) {
        jumpRow[j] = prev[prev[j]];
        costRow[j] = prevCost[j] + prevCost[prev[j]];
      }
    }
  }

  pair<int, int> query(int n, int x) const {
    int c = 0;
    for (int i = 0; i < maxDepth_; ++i) {
      if ((n >> i) & 1) {
        c += costTable_[i][x];
        x = jumpTable_[i][x];
      }
    }
    return {x, c};
  }
};

int main() {

  int N;
  scanf("%d", &N);

  vector<vector<Edge>> edges(N);
  for (int i = 0; i < N-1; ++i) {
    int u, v, w;
    scanf("%d %d %d", &u, &v, &w);
    u--; v--;
    edges[u].push_back({u, v, w});
    edges[v].push_back({v, u, w});
  }

  auto tree = TreeBuilder<true, true, true, true>::build(edges, 0);

  int maxDepth = *max_element(tree.depth.begin(), tree.depth.end());
  int logMaxDepth = log2(maxDepth) + 1;

  const auto& parent = tree.parent;
  const auto& depth = tree.depth;
  const auto& cost = tree.cost;
  
  SparseTable table(parent, cost, logMaxDepth);

  int M;
  scanf("%d", &M);
  
  for (int i = 0; i < M; ++i) {
    int q, u, v;
    scanf("%d %d %d", &q, &u, &v);
    u--; v--;
    if (q == 1) {
      int ans = 0;
      if (depth[u] < depth[v]) {
        swap(u, v);
      }
      if (depth[u] > depth[v]) {
        auto [u2, c] = table.query(depth[u] - depth[v], u);
        u = u2;
        ans += c;
      }
      for (int i = logMaxDepth; i >= 0; --i) {
        auto [u2, c1] = table.query(1<<i, u);
        auto [v2, c2] = table.query(1<<i, v);
        if (u2 != v2 && u2 != 0) {
          u = u2;
          v = v2;
          ans += c1;
          ans += c2;
        }
      }
      if (u != v) {
        auto [u2, c1] = table.query(1, u);
        auto [v2, c2] = table.query(1, v);
        ans += c1;
        ans += c2;
      }
      printf("%d\n", ans);
    }
  }

  return 0;
}
