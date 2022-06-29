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

int topologicalSort(const vector<vector<int>>& graph) {
  size_t N = graph.size();
  vector<int> incomming(N, 0);
  for (int u = 0; u < graph.size(); ++u) {
    for (int v : graph[u]) {
      incomming[v]++;
    }
  }
  int res = 0;
  for (int v = 0; v < N; ++v) {
    if (incomming[v] == 0) {
      res++;
    }
  }
  return res;
}

void solution() {
  int N, M;
  scanf("%d %d", &N, &M);
  
  vector<vector<int>> edges(N);
  for (int i = 0; i < M; ++i) {
    int u, v;
    scanf("%d %d", &u, &v);
    u--; v--;
    edges[u].push_back(v);
  }

  auto sccs = tarjanSCC(edges);
  map<int, int> sccInv;
  for (int gid = 0; gid < sccs.size(); ++gid) {
    for (int v : sccs[gid]) {
      sccInv[v] = gid;
    }
  }

  vector<vector<int>> groupEdges(sccs.size());
  for (int u = 0; u < N; ++u) {
    for (int v : edges[u]) {
      int gu = sccInv[u];
      int gv = sccInv[v];
      if (gu != gv) {
        groupEdges[gu].push_back(gv);
      }
    }
  }

  int ans = topologicalSort(groupEdges);
  printf("%d\n", ans);
  
}

int main() {

  int T;
  scanf("%d", &T);
  
  while(T--) {
    solution();
  }

  return 0;
}
