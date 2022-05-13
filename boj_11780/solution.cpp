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

vector<int> trace(const vector<vector<LL>>& cost, int i, int j) {
  for (int k = 1; k < cost.size(); ++k) {
    if (k == i || k == j) {
      continue;
    }
    if (cost[i][k] + cost[k][j] == cost[i][j]) {
      auto l = trace(cost, i, k);
      auto r = trace(cost, k, j);
      l.pop_back();
      l.insert(l.end(), r.begin(), r.end());
      return l;
    }
  }
  return vector<int>{i, j};
}

int main() {
  int N, M;
  scanf("%d %d", &N, &M);

  vector<vector<LL>> adj(N + 1, vector<LL>(N + 1, INF));
  for (int i = 0; i <= N; ++i) {
    adj[i][i] = 0;
  }
  for (int i = 0; i < M; ++i) {
    int A, B, C;
    scanf("%d %d %d", &A, &B, &C);
    adj[A][B] = min((LL)C, adj[A][B]);
  }

  // for (int i = 1; i < adj.size(); ++i) {
  // for(int j = 1; j < adj[i].size(); ++j) {
  // printf("%d ", adj[i][j]);
  //}
  // printf("\n");
  //}

  auto cost = floydWarshall(adj);
  for (int i = 1; i < cost.size(); ++i) {
    for (int j = 1; j < cost[i].size(); ++j) {
      printf("%lld ", cost[i][j] == INF ? 0 : cost[i][j]);
    }
    printf("\n");
  }
  for (int i = 1; i < cost.size(); ++i) {
    for (int j = 1; j < cost[i].size(); ++j) {
      if (i == j) {
        printf("0\n");
      } else if (cost[i][j] == INF) {
        printf("0\n");
      } else {
        auto t = trace(cost, i, j);
        printf("%d ", t.size());
        for (int i = 0; i < t.size(); ++i) {
          printf("%d ", t[i]);
        }
        printf("\n");
      }
    }
  }

  return 0;
}
