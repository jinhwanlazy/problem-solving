#include <bits/stdc++.h>
using namespace std;

static constexpr int INF = numeric_limits<int>::max();

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
  int N, M, X;
  scanf("%d %d %d", &N, &M, &X);
  X--;
  
  vector<vector<int>> graph(N, vector<int>(N, INF));
  for (int i = 0; i < N; ++i)  {
    graph[i][i] = 0;
  }
  for (int i = 0; i < M; ++i) {
    int u, v, t;
    scanf("%d %d %d", &u, &v, &t);
    u--; v--;
    graph[u][v] = t;
  }

  FloydWarshall fw(graph);
  fw.solve();
  auto res = fw.cost();
  
  int ans = 0;
  for (int i = 0; i < N; ++i) {
    if (i == X) {
      continue;
    }
    if (res[X][i] == INF || res[i][X] == INF) {
      continue;
    }
    ans = max(ans, res[X][i] + res[i][X]);
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
