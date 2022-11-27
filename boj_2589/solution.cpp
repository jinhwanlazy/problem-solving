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

    for (size_t k = 0; k < N; ++k) {
      for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
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

int maxDepth(const vector<vector<int>>& graph, int startIdx) {
  vector<bool> visited(graph.size(), false);
  vector<int> idxs{startIdx};
  int depth = -1;
  while (!idxs.empty()) {
    vector<int> idxsSwap;
    for (int i : idxs) {
      if (visited[i]) {
        continue;
      }
      visited[i] = true;
      for (int j : graph[i]) {
        if (!visited[j]) {
          idxsSwap.push_back(j);
        }
      }
    }
    idxsSwap.swap(idxs);
    depth++;
  }
  return depth;
}

void solve() {
  int N, M;
  scanf("%d %d", &N, &M);

  vector<pair<int, int>> lands;
  vector<vector<char>> W(N, vector<char>(M));
  vector<vector<int>> landIdx(N, vector<int>(M, -1));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      scanf(" %c", &W[i][j]);
      landIdx[i][j] = lands.size();
      if (W[i][j] == 'L') {
        lands.push_back({i, j});
      }
    }
  }

  vector<vector<int>> graph(lands.size());
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      if (W[i][j] == 'L' && i < N-1 && W[i+1][j] == 'L') {
        graph[landIdx[i][j]].push_back(landIdx[i+1][j]);
        graph[landIdx[i+1][j]].push_back(landIdx[i][j]);
      }
      if (W[i][j] == 'L' && j < M-1 && W[i][j+1] == 'L') {
        graph[landIdx[i][j]].push_back(landIdx[i][j+1]);
        graph[landIdx[i][j+1]].push_back(landIdx[i][j]);
      }
    }
  }


  int ans = 0;
  for (size_t start = 0; start < graph.size(); ++start) {
    ans = max(ans, maxDepth(graph, start));
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
