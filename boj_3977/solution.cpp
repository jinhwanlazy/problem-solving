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

vector<int> topologicalSort(const vector<vector<int>>& graph, int& countStart) {
  size_t N = graph.size();
  vector<int> incomming(N, 0);
  for (int u = 0; u < graph.size(); ++u) {
    for (int v : graph[u]) {
      incomming[v]++;
    }
  }

  queue<int> Q;
  for (int v = 0; v < N; ++v) {
    if (incomming[v] == 0) {
      Q.push(v);
      countStart++;
    }
  }

  vector<int> res;
  while (!Q.empty()) {
    int u = Q.front(); Q.pop();
    res.push_back(u);
    for (int v : graph[u]) {
      incomming[v]--;
      if (incomming[v] == 0) {
        Q.push(v);
      }
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
    edges[u].push_back(v);
  }

  auto sccs = tarjanSCC(edges);
  map<int, int> sccInv;
  for (int i = 0; i < sccs.size(); ++i) {
    for (int v : sccs[i]) {
      sccInv[v] = i;
    }
  }

  if (sccs.size() == 1) {
    for (int i = 0; i < N; ++i) {
      printf("%d\n", i);
    }
    printf("\n");
    return;
  }

  vector<vector<int>> gEdges(sccs.size());
  for (int u = 0; u < edges.size(); ++u) {
    for (int v : edges[u]) {
      int gu = sccInv[u];
      int gv = sccInv[v];
      if (gu != gv) {
        gEdges[gu].push_back(gv);
      }
    }
  }

  int countStartGroups = 0;
  auto gOrder = topologicalSort(gEdges, countStartGroups);
  if (countStartGroups > 1 || gOrder.size() < gEdges.size()) {
    printf("Confused\n\n");
  }
  else {
    auto& scc = sccs[gOrder.front()];
    sort(all(scc));
    for (int i : scc) {
      printf("%d\n", i);
    }
    printf("\n");
  }
}

int main() {
  int T;
  scanf("%d", &T);
  
  while (T--) {
    solution();
  }

  return 0;
}
