#include <bits/stdc++.h>
#include <limits>
using namespace std;

using LL = long long;
constexpr static LL INF = numeric_limits<int>::max();

vector<vector<LL>> floydWarshall(const vector<vector<LL>>& adj) {
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
  int N, M;
  scanf("%d %d", &N, &M);
  
  vector<vector<LL>> adj(N, vector<LL>(N, INF));
  for (int i = 0; i < N; ++i) {
    adj[i][i] = 0;
  }
  for (int i = 0; i < M; ++i) {
    int a, b;
    scanf("%d %d", &a, &b);
    a--;
    b--;
    adj[a][b] = 1;
    adj[b][a] = 1;
  }
  
  auto cost = floydWarshall(adj);

  int ans = 1;
  LL min_kb = INF;
  for (int i = 0; i < N; ++i) {
    LL kb = 0;
    for (int j = 0; j < N; ++j) {
      kb += cost[i][j];
    }
    if (min_kb > kb) {
      ans = i;
      min_kb = kb;
    }
  }
  printf("%d\n", ans+1);
  
  return 0;
}
