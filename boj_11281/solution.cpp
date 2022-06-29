#include <bits/stdc++.h>
#include <cstdio>
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
  int N, M;
  scanf("%d %d", &N, &M);

  const auto neg = [N](int i) -> int { return (i < N) ? i + N : i - N; };

  vector<vector<int>> edges(2*N);
  for (int i = 0; i < M; ++i) {
    int a, b;
    scanf("%d %d", &a, &b);

    a = (a < 0) ? N - (a + 1) : a - 1;
    b = (b < 0) ? N - (b + 1) : b - 1;

    edges[neg(a)].push_back(b);
    edges[neg(b)].push_back(a);
  }

  auto ans = twoSAT(edges, neg);
  if (ans.empty()) {
    printf("0\n");
  }
  else {
    printf("1\n");
    for (bool b : ans) {
      printf("%d ", b);
    }
  }
  return 0;
}

