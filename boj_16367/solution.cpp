#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()

using namespace std;
using LL = long long;

vector<vector<int>> tarjanSCC(const vector<vector<int>>& edges) {
  struct Vertex {
    int vid;
    int index = -1;
    bool processed = false;
  };
  vector<vector<int>> res;
  stack<Vertex*> S;
  vector<Vertex> vertices(edges.size());
  for (int i = 0; i < edges.size(); ++i) {
    vertices[i].vid = i;
  }
  int index = 0;

  function<int(Vertex&)> dfs = [&](Vertex& v) -> int {
    v.index = index++;
    S.push(&v);
    int parent = v.index;
    for (int nxt : edges[v.vid]) {
      Vertex& w = vertices[nxt];
      if (w.index == -1) {
        parent = min(parent, dfs(w));
      } else if (!w.processed) {
        parent = min(parent, w.index);
      }
    }
    if (parent == v.index) {
      vector<int> newSCC;
      Vertex* w;
      do {
        w = S.top();
        S.pop();
        w->processed = true;
        newSCC.push_back(w->vid);
      } while (w->vid != v.vid);
      res.push_back(newSCC);
    }
    return parent;
  };

  for (auto& v : vertices) {
    if (v.index == -1) {
      dfs(v);
    }
  }

  return res;
}


vector<bool> twoSAT(const vector<vector<int>>& graph,
                    const function<int(int)>& neg) {
  auto sccs = tarjanSCC(graph);
  size_t N = graph.size() / 2;

  vector<int> sccGroup(graph.size());
  for (int i = 0; i < sccs.size(); ++i) {
    const auto& scc = sccs[i];
    for (int j : scc) {
      sccGroup[j] = i;
    }
  }

  for (int i = 0; i < N; ++i) {
    if (sccGroup[i] == sccGroup[neg(i)]) {
      return {};
    }
  }

  vector<bool> res(N);
  for (int i = 0; i < res.size(); ++i) {
    res[i] = sccGroup[i] < sccGroup[neg(i)];
  }
  return res;
}

int main() {
  int K, N;
  scanf("%d %d", &K, &N);

  auto neg = [K](int x) -> int { return (x < K) ? x + K : x - K; };

  vector<vector<int>> graph(2 * K);
  for (int i = 0; i < N; ++i) {
    int x, y, z;
    char p, q, r;
    scanf("%d %c %d %c %d %c", &x, &p, &y, &q, &z, &r);
    x--; y--; z--;

    if (p == 'B') x = neg(x);
    if (q == 'B') y = neg(y);
    if (r == 'B') z = neg(z);
    
    graph[neg(x)].push_back(y);
    graph[neg(y)].push_back(x);
    graph[neg(x)].push_back(z);
    graph[neg(z)].push_back(x);
    graph[neg(y)].push_back(z);
    graph[neg(z)].push_back(y);
  }

  vector<bool> res = twoSAT(graph, neg);
  if (res.empty()) {
    printf("%d\n", -1);
  }
  else {
    for (int i = 0; i < res.size(); ++i) {
      printf("%c", res[i] ? 'R' : 'B');
    }
    printf("\n");
  }
  

  return 0;
}
