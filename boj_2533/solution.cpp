#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  Solution(int N) : N(N), tree(N), memo(2, vector<int>(N, -1)) {}

  void read() {
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
      ans = use ? 1 : 0;
    } else if (use == 1) {
      ans = 1;
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

  int N;
  vector<vector<int>> tree;
  vector<vector<int>> memo;
};

int main() {
  int N;
  scanf("%d", &N);

  Solution solution(N);
  solution.read();

  int max_set = max(solution.solve(0, 0), solution.solve(0, 1));

  printf("%d\n", N - max_set);
  return 0;
}
