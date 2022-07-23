#include <bits/stdc++.h>
using namespace std;
using LL = long long;
constexpr static LL INF = numeric_limits<LL>::max() >> 1;

struct Edge {
  int u;
  int v;
  LL cost;
};

bool bellmanFord(const vector<Edge>& edges, int nVertices, int src, vector<LL>& cost) {
  cost.resize(nVertices);
  fill(cost.begin(), cost.end(), INF);
  cost[src] = true;

  for (int i = 0; i < nVertices; ++i) {
    for (const auto& [u, v, c] : edges) {
      if (cost[u] != INF && cost[v] > cost[u] + c) {
        cost[v] = cost[u] + c;
        if (i == nVertices-1) {
          return false;
        }
      }
    }
  }
  return true;
}


void solve() {
  int N, M, W;
  scanf("%d %d %d", &N, &M, &W);
  
  vector<Edge> edges;
  for (int i = 0; i < M; ++i) {
    int u, v;
    LL w;
    scanf("%d %d %lld", &u, &v, &w);
    u--; v--;
    edges.push_back({u, v, w});
    edges.push_back({v, u, w});
  }

  for (int i = 0; i < W; ++i) {
    int u, v;
    LL w;
    scanf("%d %d %lld", &u, &v, &w);
    u--; v--;
    edges.push_back({u, v, -w});
  }

  vector<LL> cost;
  if (bellmanFord(edges, N, 0, cost)) {
    printf("NO\n");
  }
  else {
    printf("YES\n");
  }
}

int main() {
  int T;
  scanf("%d", &T);

  while (T--) {
    solve();
  }

  return 0;
}
