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
  int N, M;
  cin >> N >> M;

  vector<vector<int>> G(N, vector<int>(N, INF));

  for (int i = 0; i < M; ++i) {
    int u, v;
    cin >> u >> v;
    --u; --v;
    G[u][v] = 0;
  }

  FloydWarshall fw(G);
  fw.solve();

  auto C = fw.cost();
  int ans = 0;
  for (int i = 0; i < N; ++i) {
    bool known = true;
    for (int j = 0; j < N; ++j) {
      if (i == j) 
        continue;
      if (C[i][j] == INF && C[j][i] == INF) {
        known = false;
        break;
      }
    }
    ans += !known;
  }
  cout << N - ans << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL); cout.tie(NULL);

  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
