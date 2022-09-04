#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> tarjanSCC(const vector<vector<int>>& edges) {
  struct Vertex {
    int vid = -1;
    int index = -1;
    bool processed = false;
  };
  vector<vector<int>> res;
  stack<Vertex*> S;
  vector<Vertex> vertices(edges.size());
  for (size_t i = 0; i < edges.size(); ++i) {
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

void solve() {
  int N;
  scanf("%d", &N);

  vector<vector<int>> edges(N);
  for (int i = 0; i < N; ++i) {
    int j;
    scanf("%d", &j);
    edges[i].push_back(j - 1);
  }

  auto sccs = tarjanSCC(edges);

  int ans = N;
  for (auto& group : sccs) {
    if (group.size() == 1) {
      ans -= edges[group[0]][0] == group[0];
    } else {
      ans -= group.size();
    }
  }
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
