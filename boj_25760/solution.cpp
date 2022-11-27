#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> buildTree(const vector<vector<int>>& edges, int root) {
  int N = edges.size();
  vector<vector<int>> tree(N);
  vector<int> visited(N, false);
  vector<int> st;
  st.push_back(root);
  while (!st.empty()) {
    int u = st.back(); st.pop_back();
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

vector<bool> merge(bool first, const vector<vector<bool>>& vs) {
  vector<int> idxs(vs.size(), 0);
  vector<bool> res = {first};

  for (int i = 0; i < vs.size(); ++i) {
    int& idx = idxs[i];
    if (vs[i].size() > idx && vs[i][idx] == 0) {
      idx++;
    }
  }
  while (true) {
    bool end = true;
    bool car = false;
    for (int i = 0; i < vs.size(); ++i) {
      int& idx = idxs[i];
      if (vs[i].size() == idx) {
        continue;
      }
      end = false;
      if (vs[i][idx]) {
        if (car) {
          continue;
        }
        else {
          car = true;
          idx++;
        }
      }
      else {
        idx++;
      }
    }
    if (end) {
      break;
    }
    res.push_back(car);
  }
  return res;
}

vector<bool> solve(const vector<vector<int>>& tree, const vector<int>& cars, int idx) {
  if (tree[idx].empty()) {
    if (cars[idx]) {
      return {1};
    }
    else {
      return {};
    }
  }
  vector<vector<bool>> children;
  for (int j : tree[idx]) {
    auto v = solve(tree, cars, j);
    if (!v.empty()) {
      children.push_back(v);
    }
  }

  printf("%d\n", idx+1);
  auto res = merge(cars[idx], children);
  for (int i = 0; i < res.size(); ++i) {
    printf("%d ", (int)res[i]);
  }
  printf("\n");
  
  return res;
}

void solve() {
  int N;
  scanf("%d", &N);

  vector<vector<int>> graph(N);
  for (int i = 0; i < N-1; ++i) {
    int u, v;
    scanf("%d %d", &u, &v);
    u--;
    v--;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  vector<int> cars(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &cars[i]);
  }

  auto tree = buildTree(graph, 0);
  auto res = solve(tree, cars, 0);
  printf("%llu\n", res.size());
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
