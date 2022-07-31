#include <bits/stdc++.h>
#include <limits>
using namespace std;

constexpr static int di[4] = {1, 0, -1, 0};
constexpr static int dj[4] = {0, 1, 0, -1};

class Dinic {
 public:
  using flow_t = int;
  constexpr static flow_t INF = numeric_limits<flow_t>::max();

  int N_;
  int src_;
  int sink_;
  map<pair<int, int>, flow_t> cap_ = {};
  map<pair<int, int>, flow_t> flow_ = {};
  vector<set<int>> graph_;

  Dinic(int N)
      : N_(N),
        src_(0),
        sink_(N - 1),
        graph_(vector<set<int>>(N)) {}

  void addEdge(int u, int v, flow_t cap) {
    cap_[{u, v}] = cap;
    graph_[u].insert(v);
    graph_[v].insert(u);
  }

  void setSrcSink(int src, int sink) {
    src_ = src;
    sink_ = sink;
  }

  flow_t solve() {
    flow_t res = 0;
    vector<int> level;
    vector<set<int>::iterator> skipIdx(N_);
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
  bool buildLevelGraph(vector<int>& level) {
    level.resize(N_);
    fill(level.begin(), level.end(), -1);
    level[src_] = 0;

    queue<int> Q;
    Q.push(src_);
    while (!Q.empty()) {
      int u = Q.front();
      Q.pop();
      for (int v : graph_[u]) {
        if (level[v] == -1 && cap_[{u, v}] - flow_[{u, v}] > 0) {
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
            vector<set<int>::iterator>& skipIdx) {
    if (u == sink_) {
      return maxFlow;
    }
    for (auto& it = skipIdx[u]; it != graph_[u].end(); ++it) {
      int v = *it;
      flow_t cap = cap_[{u, v}] - flow_[{u, v}];
      if (level[u] + 1 == level[v] && cap > 0) {
        flow_t f = letFlow(v, min(maxFlow, cap), level, skipIdx);
        if (f > 0) {
          flow_[{u, v}] += f;
          flow_[{v, u}] -= f;
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

  int src = -1;
  int sink = -1;
  map<pair<int, int>, int> idx;

  vector<vector<char>> grid(N, vector<char>(M));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      scanf(" %c", &grid[i][j]);
      if (grid[i][j] == '#') {
        continue;
      }
      idx[{i, j}] = idx.size() * 2;
      if (grid[i][j] == 'K') {
        src = idx[{i, j}];
      }
      if (grid[i][j] == 'H') {
        sink = idx[{i, j}];
      }
    }
  }

  Dinic maxflow(idx.size()*2);
  maxflow.setSrcSink(src+1, sink);

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      if (grid[i][j] == '#') {
        continue;
      }
      int u = idx[{i, j}];
      maxflow.addEdge(u, u+1, 1);
      for (int k = 0; k < 4; ++k) {
        int ii = i + di[k];
        int jj = j + dj[k];
        if (!(0 <= ii && ii < N && 0 <= jj && jj < M)) {
          continue;
        }
        if (grid[ii][jj] == '#')  {
          continue;
        }
        int v = idx[{ii, jj}];
        maxflow.addEdge(u+1, v, 1);
      }
    }
  }

  if (maxflow.cap_[{src+1, sink}] > 0) {
    printf("%d\n", -1);
    return;
  }

  int ans = maxflow.solve();
  printf("%d\n", ans);
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
