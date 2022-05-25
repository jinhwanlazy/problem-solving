#include <bits/stdc++.h>
using namespace std;

using LL = long long;
constexpr static LL INF = numeric_limits<int>::max();

template<typename T>
vector<vector<T>> floydWarshall(const vector<vector<T>>& adj) {
  size_t N = adj.size();
  auto cost = adj;

  for (int k = 0; k < N; ++k) {
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        if (cost[i][k] != INF && cost[k][j] != INF) {
          cost[i][j] = min(cost[i][k] + cost[k][j], cost[i][j]);
        }
      }
    }
  }
  return cost;
}

int main() {
  int N;
  scanf("%d", &N);

  vector<vector<int>> adj(N, vector<int>(N));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      scanf("%d", &adj[i][j]);
      if (i != j && adj[i][j] == 0) {
        adj[i][j] = INF;
      }
      if (i == j) {
        adj[i][j] = 1;
      }
    }
  }

  auto cost = floydWarshall(adj);
  for (int i = 0; i < cost.size(); ++i) {
    for(int j = 0; j < cost[i].size(); ++j) {
      if (i == j) {
        cost[i][j] = 0;
      }
      else {
        cost[i][j] = cost[i][j] == INF ? 0 : 1;
      }
    }
  }
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      if (i == j) continue;
      if (cost[i][j] && cost[j][i]) {
        cost[i][i] = 1;
        continue;
      }
    }
  }
  
  for (int i = 0; i < cost.size(); ++i) {
    for(int j = 0; j < cost[i].size(); ++j) {
      printf("%d ", cost[i][j]);
    }
    printf("\n");
  }
  
  return 0;
}
