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
  int N;
  scanf("%d", &N);

  vector<vector<Edge>> edges(N + 1);
  for (int k = 1; k < N; ++k) {
    int A, B, C;
    scanf("%d %d %d", &A, &B, &C);

    edges[A].push_back({A, B, C});
    edges[B].push_back({B, A, C});
  }

  /*
   * 1. 임의의 정점에서 가장 먼 정점 w1 을 찾는다.
   * 2. w1 에서 가장 먼 정점 w2 를 찾는다.
   * 3. w1 과 w2 사이의 거리를 구한다.
   */
  auto cost = dijkstra(edges, 1);
  int w1 = 1;
  LL max_cost = cost[1];
  for (int i = 1; i <= N; ++i) {
    if (max_cost < cost[i]) {
      w1 = i;
      max_cost = cost[i];
    }
  }

  cost = dijkstra(edges, w1);
  int w2 = w1;
  max_cost = cost[w1];
  for (int i = 1; i <= N; ++i) {
    if (max_cost < cost[i]) {
      w2 = i;
      max_cost = cost[i];
    }
  }

  printf("%lld\n", max_cost);

  return 0;
}
