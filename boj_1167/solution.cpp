#include <bits/stdc++.h>
using namespace std;

using LL = long long;
constexpr static int INF = numeric_limits<int>::max();

struct State {
  int u;
  LL cost;

  friend bool operator<(const State& lhs, const State& rhs) {
    return lhs.cost > rhs.cost;
  }
};

struct Edge {
  int u;
  int v;
  LL cost;
};

vector<LL> dijkstra(const vector<vector<Edge>>& edges,
                    int src,
                    vector<int>* trace = nullptr) {
  vector<LL> cost(edges.size(), INF);
  if (trace) {
    trace->resize(edges.size());
    fill(trace->begin(), trace->end(), -1);
  }
  priority_queue<State> Q;
  cost[src] = 0;
  Q.push({src, 0});
  while (!Q.empty()) {
    auto [u, c] = Q.top();
    Q.pop();
    if (cost[u] < c) {
      continue;
    }
    for (const auto& [_, v, w] : edges[u]) {
      int next_cost = c + w;
      if (next_cost < cost[v]) {
        cost[v] = next_cost;
        Q.push({v, next_cost});
        if (trace) {
          (*trace)[v] = u;
        }
      }
    }
  }
  return cost;
}

int main() {
  int V;
  scanf("%d", &V);

  vector<vector<Edge>> edges(V + 1);
  for (int k = 0; k < V; ++k) {
    int i;
    bool end = false;
    scanf("%d", &i);
    while (true) {
      int j;
      scanf("%d", &j);
      if (j == -1) {
        end = true;
        break;
      }
      int w;
      scanf("%d", &w);
      edges[i].push_back({i, j, w});
    }
    if (end) {
      continue;
    }
  }

  auto cost = dijkstra(edges, 1);
  int w1 = 1;
  LL max_cost = cost[1];
  for (int i = 1; i <= V; ++i) {
    if (max_cost < cost[i]) {
      w1 = i;
      max_cost = cost[i];
    }
  }

  cost = dijkstra(edges, w1);
  int w2 = w1;
  max_cost = cost[w1];
  for (int i = 1; i <= V; ++i) {
    if (max_cost < cost[i]) {
      w2 = i;
      max_cost = cost[i];
    }
  }

  printf("%lld\n", max_cost);

  return 0;
}
