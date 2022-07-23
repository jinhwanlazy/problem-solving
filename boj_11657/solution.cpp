#include <bits/stdc++.h>
using namespace std;

using LL = long long;
constexpr static LL INF = numeric_limits<LL>::max();

struct Edge {
  int u;
  int v;
  LL cost;
};

vector<LL> bellmanFord(const vector<Edge>& edges, int nVertices, int src) {
  vector<LL> cost(nVertices, INF);
  cost[src] = 0;

  for (int i = 0; i < nVertices; ++i) {
    for (const auto& [u, v, c] : edges) {
      if (cost[u] != INF && cost[v] > cost[u] + c) {
        cost[v] = cost[u] + c;
        if (i == nVertices-1) {
          return {};
        }
      }
    }
  }
  return cost;
}

int main() {
  int N, M;
  scanf("%d %d", &N, &M);

  vector<Edge> edges;
  edges.reserve(M);
  for (int i = 0; i < M; ++i) {
    int A, B, C;
    scanf("%d %d %d", &A, &B, &C);
    A--; B--;
    edges.push_back({A, B, C});
  }

  auto cost = bellmanFord(edges, N, 0);
  if (cost.empty()) {
    printf("%d\n", -1);
  } else {
    for (int i = 1; i < N; ++i) {
      printf("%lld\n", cost[i] == INF ? -1 : cost[i]);
    }
  }

  return 0;
}
