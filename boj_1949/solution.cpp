#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  Solution(int N) : N(N), tree(N), weights(N), memo(2, vector<int>(N, -1)) {
    ans = 0;
  }

  void read() {
    for (int i = 0; i < N; ++i) {
      scanf("%d", &weights[i]);
    }
    vector<vector<int>> edges(N);
    for (int i = 0; i < N - 1; ++i) {
      int u, v;
      scanf("%d %d", &u, &v);
      u--;
      v--;
      edges[u].push_back(v);
      edges[v].push_back(u);
    }
    tree = build_tree(edges, 0);
  }

  vector<vector<int>> build_tree(const vector<vector<int>>& edges, int root) {
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

  int solve(int u, int use) {
    int& ans = memo[use][u];
    if (ans != -1) {
      return ans;
    }
    if (tree[u].empty()) {
      ans = use ? weights[u] : 0;
    } else if (use == 1) {
      ans = weights[u];
      for (int v : tree[u]) {
        ans += solve(v, 0);
      }
    } else {
      ans = 0;
      for (int v : tree[u]) {
        ans += max(solve(v, 0), solve(v, 1));
      }
    }
    return ans;
  }

  void trace(int u, int use, set<int>& used) {
    if (use) {
      used.insert(u);
      for (int v : tree[u]) {
        trace(v, 0, used);
      }
    } else {
      for (int v : tree[u]) {
        if (memo[0][v] > memo[1][v]) {
          trace(v, 0, used);
        } else {
          trace(v, 1, used);
        }
      }
    }
  }

  int N;
  vector<vector<int>> tree;
  vector<int> weights;
  vector<vector<int>> memo;

  int ans;
};

int main() {
  int N;
  scanf("%d", &N);

  Solution solution(N);
  solution.read();

  int ans0 = solution.solve(0, 0);
  int ans1 = solution.solve(0, 1);
  int ans = 0;
  // set<int> trace;
  if (ans0 < ans1) {
    ans = ans1;
    // solution.trace(0, 1, trace);
  } else {
    ans = ans0;
    // solution.trace(0, 0, trace);
  }

  printf("%d\n", ans);

  return 0;
}
