#include <bits/stdc++.h>
using namespace std;

constexpr static int INF = numeric_limits<int>::max();
constexpr static int di[4] = {0, 1, 0, -1};
constexpr static int dj[4] = {1, 0, -1, 0};

class Dinic {
 public:
  using flow_t = int;
  constexpr static flow_t INF = numeric_limits<flow_t>::max();

  int N_;
  int src_;
  int sink_;
  vector<vector<flow_t>> cap_;
  vector<vector<flow_t>> flow_;
  vector<vector<int>> graph_;

  Dinic(int N)
      : N_(N),
        src_(0),
        sink_(N - 1),
        cap_(vector<vector<flow_t>>(N, vector<flow_t>(N, 0))),
        flow_(vector<vector<flow_t>>(N, vector<flow_t>(N, 0))),
        graph_(vector<vector<int>>(N)) {}

  void addEdge(int u, int v, flow_t cap, bool bidirectional=false) {
    cap_[u][v] += cap;
    if (bidirectional) {
      cap_[v][u] += cap;
    }
    graph_[u].push_back(v);
    graph_[v].push_back(u);
  }

  void setSrcSink(int src, int sink) {
    src_ = src;
    sink_ = sink;
  }

  flow_t solve() {
    flow_t res = 0;
    vector<int> level;
    vector<vector<int>::iterator> skipIdx(N_);
    while (buildLevelGraph(level)) {
      for (int i = 0; i < N_; ++i) {
        skipIdx[i] = graph_[i].begin();
      }
      while (flow_t f = letFlow(src_, INF, level, skipIdx)) {
        res += f;
      }
    }
    return res;
  }

 private:
  bool buildLevelGraph(vector<int>& level) const {
    level.resize(N_);
    fill(level.begin(), level.end(), -1);
    level[src_] = 0;

    queue<int> Q;
    Q.push(src_);
    while (!Q.empty()) {
      int u = Q.front();
      Q.pop();
      for (int v : graph_[u]) {
        if (level[v] == -1 && cap_[u][v] - flow_[u][v] > 0) {
          level[v] = level[u] + 1;
          Q.push(v);
        }
      }
    }
    return level[sink_] != -1;
  }

  flow_t letFlow(int u,
            int maxFlow,
            const vector<int>& level,
            vector<vector<int>::iterator>& skipIdx) {
    if (u == sink_) {
      return maxFlow;
    }
    for (auto& it = skipIdx[u]; it != graph_[u].end(); ++it) {
      int v = *it;
      flow_t cap = cap_[u][v] - flow_[u][v];
      if (level[u] + 1 == level[v] && cap > 0) {
        flow_t f = letFlow(v, min(maxFlow, cap), level, skipIdx);
        if (f > 0) {
          flow_[u][v] += f;
          flow_[v][u] -= f;
          return f;
        }
      }
    }
    return 0;
  }
};

void solve() {
  int N, M;
  scanf("%d %d", &N, &M);

  auto index = [M](int i, int j) -> int { return M * i + j; };
  int sum = 0;

  vector<vector<int>> grid(N, vector<int>(M));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      scanf("%d", &grid[i][j]);
      sum += grid[i][j];
    }
  }

  Dinic maxFlow(M*N + 2);
  
  int src = M*N;
  int sink = M*N+1;

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      int odd = (i + j) % 2 == 1;
      int u = index(i, j);
      if (odd) {
        maxFlow.addEdge(u, sink, grid[i][j]);
      } else {
        maxFlow.addEdge(src, u, grid[i][j]);
        for (int k = 0; k < 4; ++k) {
          int ii = i + di[k];
          int jj = j + dj[k];
          if (!(0 <= ii && ii < N && 0 <= jj && jj < M)) {
            continue;
          }
          int v = index(ii, jj);
          maxFlow.addEdge(u, v, INF);
        }
      }
    }
  }

  maxFlow.setSrcSink(src, sink);
  int flow = maxFlow.solve();
  auto ans = flow + (sum - flow*2);
  printf("%d\n", ans);
}

int main() {
  int T;
  scanf("%d", &T);
  
  while (T--) {
    solve();
  }

  return 0;
}
