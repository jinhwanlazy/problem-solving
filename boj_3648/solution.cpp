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

bool solve(int N, int M) {
  auto neg = [N](int i)->int { return 2 * N - i; };

  vector<vector<int>> edges(2*N+1);
  for (int i = 0; i < M; ++i) {
    int u, v;
    scanf("%d %d", &u, &v);
    u += N;
    v += N;
    edges[neg(u)].push_back(v);
    edges[neg(v)].push_back(u);
  }
  // append edges not(1) -> 1
  edges[N-1].push_back(N+1);
  
  auto sccs = tarjanSCC(edges);
  sccs.erase(remove_if(all(sccs), [N](const vector<int>& scc)->bool { return scc[0] == N; }), sccs.end());

  vector<int> group(2*N+1, -1);
  for (int i = 0; i < sccs.size(); ++i) {
    const auto& scc = sccs[i];
    for (int u : scc) {
      group[u] = i;
    }
  }

  for (const auto& scc : sccs) {
    for (int u : scc) {
      if (group[u] == group[neg(u)]) {
        return false;
      }
    }
  }
  return true;
}

int main() {
  int N, M;
  while (cin >> N >> M) {
    printf(solve(N, M) ? "yes\n" : "no\n");
  }
}
