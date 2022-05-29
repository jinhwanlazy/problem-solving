#include <bits/stdc++.h>
#include <cstdio>
using namespace std;

vector<vector<int>> buildTree(const vector<vector<int>>& edges, int root) {
  int N = edges.size();
  vector<vector<int>> tree(N);
  vector<int> visited(N, false);
  vector<int> st;
  st.push_back(root);
  while (!st.empty()) {
    int u = st.back();
    st.pop_back();
    if (visited[u]) {
      continue;
    }
    visited[u] = true;
    for (int v : edges[u]) {
      if (visited[v]) {
        continue;
      }
      tree[u].push_back(v);
      st.push_back(v);
    }
  }
  return tree;
}

class SparseTable {
  vector<vector<int>> table_;
  int maxDepth_;

 public:
  SparseTable(const vector<int>& f, int maxDepth = 20)
      : table_(maxDepth), maxDepth_(maxDepth) {
    table_[0] = f;
    for (int i = 1; i < maxDepth; ++i) {
      const vector<int>& prev = table_[i - 1];
      vector<int>& row = table_[i];
      row.resize(prev.size());
      for (int j = 0; j < row.size(); ++j) {
        row[j] = prev[prev[j]];
      }
    }
  }

  SparseTable() {}

  int query(int n, int x) const {
    for (int i = 0; i < maxDepth_; ++i) {
      if ((n >> i) & 1) {
        x = table_[i][x];
      }
    }
    return x;
  }
};

class LCA {
  vector<int> depth_;
  int logMaxDepth_;
  SparseTable parent_;

 public:
  LCA(const vector<int>& parent, const vector<int>& depth) : depth_(depth) {
    int maxDepth = 1;
    for (auto d : depth) {
      maxDepth = max(d, maxDepth);
    }
    logMaxDepth_ = log2(maxDepth) + 2;
    parent_ = SparseTable(parent, logMaxDepth_);
  }

  int query(int u, int v) {
    if (depth_[u] < depth_[v]) {
      swap(u, v);
    }

    if (depth_[u] != depth_[v]) {
      u = parent_.query(depth_[u] - depth_[v], u);
    }

    for (int i = logMaxDepth_; i >= 0; --i) {
      int u2 = parent_.query(1 << i, u);
      int v2 = parent_.query(1 << i, v);
      if (u2 != v2 && u2 != 0) {
        u = u2;
        v = v2;
      }
    }
    if (u != v) {
      u = parent_.query(1, u);
      v = parent_.query(1, v);
    }
    return u;
  }
};

int main() {
  int N;
  scanf("%d", &N);

  vector<vector<int>> edges(N + 1);
  for (int i = 0; i < N - 1; ++i) {
    int u, v;
    scanf("%d %d", &u, &v);
    u--;
    v--;
    edges[u].push_back(v);
    edges[v].push_back(u);
  }

  vector<vector<int>> tree = buildTree(edges, 0);
  vector<int> parent(N, 0);
  vector<int> depth(N, 0);
  stack<pair<int, int>> S;
  S.push({0, 0});

  while (!S.empty()) {
    auto [i, d] = S.top();
    S.pop();
    depth[i] = d;
    for (int child : tree[i]) {
      parent[child] = i;
      S.push({child, d + 1});
    }
  }

  LCA lca(parent, depth);

  int M;
  scanf("%d", &M);
  while (M--) {
    int u, v;
    scanf("%d %d", &u, &v);
    u--;
    v--;

    printf("%d\n", lca.query(u, v) + 1);
  }
  return 0;
}
