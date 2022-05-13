#include <bits/stdc++.h>
using namespace std;

constexpr static int MOD = 10000;

constexpr static int INF = numeric_limits<int>::max();

struct State {
  int u;
  int cost;

  friend bool operator<(const State& lhs, const State& rhs) {
    return lhs.cost > rhs.cost;
  }
};

struct Edge {
  int u;
  int v;
  char cmd;
  int cost;
};

struct Trace {
  int prev;
  char cmd;
};

vector<int> dijkstra(const vector<vector<Edge>>& edges,
                     int src,
                     int dst,
                     vector<Trace>* trace = nullptr) {
  vector<int> cost(edges.size(), INF);
  if (trace) {
    trace->resize(edges.size());
    // fill(trace->begin(), trace->end(), {-1, 0});
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
    if (u == dst) {
      break;
    }

    for (const auto& [_, v, cmd, w] : edges[u]) {
      int next_cost = c + w;
      if (next_cost < cost[v]) {
        cost[v] = next_cost;
        Q.push({v, next_cost});
        if (trace) {
          (*trace)[v] = {u, cmd};
        }
      }
    }
  }
  return cost;
}

int main() {
  int T;
  scanf("%d", &T);

  vector<vector<Edge>> edges(MOD);
  for (int i = 0; i < MOD; ++i) {
    if (i != 0) {
      edges[i].push_back({i, (2 * i) % MOD, 'D', 1});
    }
    edges[i].push_back({i, i == 0 ? 9999 : (i - 1) % MOD, 'S', 1});
    edges[i].push_back({i, i / 1000 + (i % 1000) * 10, 'L', 1});
    edges[i].push_back({i, i / 10 + (i % 10) * 1000, 'R', 1});
  }

  while (T--) {
    int src, dst;
    scanf("%d %d", &src, &dst);

    vector<Trace> trace;
    auto cost = dijkstra(edges, src, dst, &trace);

    vector<char> ans;
    while (dst != src) {
      auto& t = trace[dst];
      ans.push_back(t.cmd);
      dst = t.prev;
    }
    for (int i = ans.size(); i > 0; --i) {
      cout << ans[i - 1];
    }
    printf("\n");
  }
  return 0;
}
