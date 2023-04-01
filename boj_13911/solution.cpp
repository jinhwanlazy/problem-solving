#include <bits/stdc++.h>
using namespace std;

using LL = long long;
constexpr LL INF = numeric_limits<LL>::max() / 2;

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

vector<LL> computeDistances(const vector<vector<Edge>>& graph,
                            const vector<int>& stores) {
  vector<LL> res(graph.size(), INF);

  priority_queue<State> pq;
  vector<bool> visited(graph.size(), false);
  for (int u : stores) {
    pq.push({u, 0});
  }

  while (!pq.empty()) {
    auto [u, dist] = pq.top();
    pq.pop();
    if (res[u] < INF)
      continue;
    res[u] = dist;
    for (const auto& [_, v, w] : graph[u]) {
      if (res[v] == INF) {
        pq.push({v, dist + w});
      }
    }
  }
  return res;
}

void solve() {
  int V, E;
  cin >> V >> E;

  vector<vector<Edge>> graph(V + 1);
  for (int i = 0; i < E; ++i) {
    int u, v, c;
    cin >> u >> v >> c;
    graph[u].push_back({u, v, c});
    graph[v].push_back({v, u, c});
  }

  int M;
  LL x;
  cin >> M >> x;
  vector<int> ms(M);
  for (int i = 0; i < M; ++i) {
    cin >> ms[i];
  }

  int S;
  LL y;
  cin >> S >> y;
  vector<int> ss(S);
  for (int i = 0; i < S; ++i) {
    cin >> ss[i];
  }

  auto md = computeDistances(graph, ms);
  auto sd = computeDistances(graph, ss);

  for (int i : ms)
    md[i] = INF;
  for (int i : ss)
    sd[i] = INF;

  // for (int i = 0; i < md.size(); ++i) {
  // cout << ((md[i] == INF) ? -1 : md[i]) << ", ";
  //}
  // cout << "\n";
  // for (int i = 0; i < sd.size(); ++i) {
  // cout << ((sd[i] == INF) ? -1 : sd[i]) << ", ";
  //}
  // cout << "\n";

  LL ans = INF;
  for (int i = 1; i <= V; ++i) {
    if (md[i] > x || sd[i] > y) {
      continue;
    }
    ans = min(ans, md[i] + sd[i]);
  }
  if (ans == INF)
    ans = -1;
  cout << ans << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
