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

int main() {
  int V, E;
  scanf("%d %d", &V, &E);

  vector<vector<int>> edges(V);
  for (int i = 0; i < E; ++i) {
    int u, v;
    scanf("%d %d", &u, &v);

    u--;
    v--;
    edges[u].push_back(v);
  }

  auto sccs = tarjanSCC(edges);
  for (auto& scc : sccs) {
    sort(all(scc));
  }
  sort(all(sccs), [](const auto& lhs, const auto& rhs) -> bool {
    return lhs.front() < rhs.front();
  });

  printf("%lu\n", sccs.size());
  for (int i = 0; i < sccs.size(); ++i) {
    for (int j = 0; j < sccs[i].size(); ++j) {
      printf("%d ", sccs[i][j] + 1);
    }
    printf("-1\n");
  }

  return 0;
}
