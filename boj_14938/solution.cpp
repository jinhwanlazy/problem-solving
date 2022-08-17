#include <bits/stdc++.h>
using namespace std;

constexpr static int INF = numeric_limits<int>::max();

class FloydWarshall {
 public:
  using T = int;

  const vector<vector<T>>& graph_;
  vector<vector<T>> costs_;
  FloydWarshall(const vector<vector<T>>& graph) : graph_(graph), costs_(0) {}

  void solve() {
    size_t N = graph_.size();
    costs_ = graph_;

    for (int k = 0; k < N; ++k) {
      for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
          if (costs_[i][k] != INF && costs_[k][j] != INF) {
            costs_[i][j] = min(costs_[i][k] + costs_[k][j], costs_[i][j]);
          }
        }
      }
    }
  }

  const vector<vector<T>>& cost() const {
    return costs_;
  }
};

void solve() {
  int n, m, r;
  scanf("%d %d %d", &n, &m, &r);

  vector<int> ts(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &ts[i]);
  }

  vector<vector<int>> graph(n, vector<int>(n, INF));
  for (int i = 0; i < r; ++i) {
    int u, v, l;
    scanf("%d %d %d", &u, &v, &l);
    u--;
    v--;
    graph[u][v] = graph[v][u] = l;
  }
  for (int i = 0; i < n; ++i) {
    graph[i][i] = 0;
  }

  FloydWarshall floyd(graph);
  floyd.solve();

  int ans = 0;
  auto cost = floyd.cost();

  for (int i = 0; i < n; ++i) {
    int tmp = 0;
    for (int j = 0; j < n; ++j) {
      if (cost[i][j] <= m) {
        tmp += ts[j];
      }
    }
    ans = max(ans, tmp);
  }
  printf("%d\n", ans);
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
