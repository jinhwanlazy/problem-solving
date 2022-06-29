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

int main() {
  int N, M;
  scanf("%d %d", &N, &M);

  vector<vector<int>> edges(2*N + 2);
  for (int i = 0; i < M; ++i) {
    int a, b;
    scanf("%d %d", &a, &b);

    int notA = -a;
    int notB = -b;

    a += N;
    b += N;
    notA += N;
    notB += N;

    edges[notA].push_back(b);
    edges[notB].push_back(a);
  }
  
  auto sccs = tarjanSCC(edges);

  bool fail = false;
  for (const auto& scc : sccs) {
    if (scc[0] == N) {
      continue;
    }
    set<int> sccSet(all(scc));
    for (int i : scc) {
      int notI = 2 * N - i;
      if (sccSet.find(notI) != sccSet.end()) {
        //printf("fail %d - %d\n", i-N, notI-N);
        fail = true;
        break;
      }
    }
    if (fail) {
      break;
    }
  }
  
  printf("%d", fail ? 0 : 1);
  return 0;
}
