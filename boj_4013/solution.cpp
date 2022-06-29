#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
using namespace std;

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

void invSCC(const vector<vector<int>>& edges,
            const vector<vector<int>>& sccs,
            map<int, int>& v2scc,
            vector<vector<int>>& sccEdges) {
  v2scc.clear();
  for (int sccId = 0; sccId < sccs.size(); ++sccId) {
    for (int v : sccs[sccId]) {
      v2scc[v] = sccId;
    }
  }

  sccEdges.clear();
  sccEdges.resize(sccs.size());
  for (int u = 0; u < edges.size(); ++u) {
    int gu = v2scc[u];
    for (int v : edges[u]) {
      int gv = v2scc[v];
      if (gu != gv) {
        sccEdges[gu].push_back(gv);
      }
    }
  }
}

int main() {
  int N, M;
  scanf("%d %d", &N, &M);
  
  vector<vector<int>> roads(N);
  for(int i = 0; i < M; ++i) {
    int u, v;
    scanf("%d %d", &u, &v);
    u--; v--;
    roads[u].push_back(v);
  }
  for (auto& vs : roads) {
    vs.shrink_to_fit();
  }

  // group edges in SCC
  auto sccs = tarjanSCC(roads);
  for (auto& vs : sccs) {
    vs.shrink_to_fit();
  }

  map<int, int> v2scc;
  vector<vector<int>> sccEdges;
  invSCC(roads, sccs, v2scc, sccEdges);

  vector<vector<int>>().swap(roads);

  vector<int> sccCaches(sccs.size());
  for (int i = 0; i < N; ++i) {
    int c;
    scanf("%d", &c);
    sccCaches[v2scc[i]] += c;
  }

  int S, P;
  scanf("%d %d", &S, &P);
  S = v2scc[--S];

  vector<bool> sccHasTerminal(sccEdges.size());
  for (int i = 0; i < P; ++i) {
    int v;
    scanf("%d", &v);
    v--;
    sccHasTerminal[v2scc[v]] = true;
  }

  v2scc.clear();

  // remove edges from vertices that cannot be visited
  stack<int> st;
  vector<bool> visited(sccEdges.size());
  st.push(S);
  while (!st.empty()) {
    int u = st.top(); st.pop();
    visited[u] = true;
    for (int v : sccEdges[u]) {
      if (!visited[v]) {
        st.push(v);
      }
    }
  }
  for (int u = 0; u < sccEdges.size(); ++u)  {
    if (!visited[u]) {
      sccEdges[u].clear();
    }
  }

  // dp[i] := the maximum cache collected at the vertex_i
  vector<int> dp(sccEdges.size(), 0);
  vector<vector<int>> prevs(sccEdges.size());
  vector<int> incomming(sccEdges.size(), 0);
  for (int u = 0; u < sccEdges.size(); ++u) {
    for (int v : sccEdges[u]) {
      incomming[v]++;
      prevs[v].push_back(u);
    }
  }

  queue<int> Q;
  Q.push(S);
  dp[S] = sccCaches[S];

  while (!Q.empty()) {
    auto u = Q.front(); Q.pop();
    for (int v : sccEdges[u]) {
      incomming[v]--;
      dp[v] = max(dp[v], sccCaches[v] + dp[u]);
      if (incomming[v] == 0) {
        Q.push(v);
      }
    }
  }

  int ans = 0;
  for (int u = 0; u < sccEdges.size(); ++u) {
    if (sccHasTerminal[u]) {
      ans = max(ans, dp[u]);
    }
  }
  
  //for (int i = 0; i < sccs.size(); ++i) {
    //for(int j = 0; j < sccs[i].size(); ++j) {
      //printf("%d ", sccs[i][j]);
    //}
    //printf("- %d ", dp[i]);
    //printf(" - %d ", sccCaches[i]);
    //printf("\n");
  //}
  
  printf("%d\n", ans);
  return 0;
}
