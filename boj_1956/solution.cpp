#include <bits/stdc++.h>
using namespace std;

using LL = long long;
constexpr static LL INF = numeric_limits<int>::max();

vector<vector<LL>> floydWarshall(const vector<vector<LL>>& adj) {
  size_t N = adj.size() - 1;
  auto cost = adj;

  for (int k = 1; k <= N; ++k) {
    for (int i = 1; i <= N; ++i) {
      for (int j = 1; j <= N; ++j) {
        if (cost[i][k] != INF && cost[k][j] != INF) {
          cost[i][j] = min(cost[i][k] + cost[k][j], cost[i][j]);
        }
      }
    }
  }
  return cost;
}

int main() {
  int V, E;
  scanf("%d %d", &V, &E);

  vector<vector<LL>> adj(V + 1, vector<LL>(V + 1, INF));
  for (int i = 1; i <= V; ++i) {
    adj[i][i] = 0;
  }
  for (int i = 0; i < E; ++i) {
    int A, B, C;
    scanf("%d %d %d", &A, &B, &C);
    adj[A][B] = min(adj[A][B], (LL)C);
  }

  auto cost = floydWarshall(adj);
  LL ans = INF;
  for (int i = 1; i < V; ++i) {
    for (int j = i + 1; j <= V; ++j) {
      LL fwd = cost[i][j];
      LL bwd = cost[j][i];
      if (fwd != INF && bwd != INF) {
        ans = min(ans, fwd + bwd);
      }
    }
  }
  printf("%lld\n", ans == INF ? -1L : ans);

  return 0;
}
