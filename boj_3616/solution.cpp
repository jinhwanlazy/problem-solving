#include <bits/stdc++.h>
using namespace std;
using LL = long long;

struct Edge
{
  int i;
  int u;
  int v;
  LL d; /* distance */
  LL c = 0; /* count prev */
};

int main() {
  LL N;
  int K, H, C;
  scanf("%lld %d %d %d", &N, &K, &H, &C);

  vector<vector<Edge>> graph(N);
  for (int i = 0; i < N-1; ++i) {
    int u, v, d;
    scanf("%d %d %d", &u, &v, &d);
    u--; v--;
    graph[u].push_back({i+1, u, v, d});
    graph[v].push_back({i+1, v, u, d});
  }
  
  vector<int> S;
  for (int u = 0; u < N; ++u) {
    if (graph[u].size() == 1) {
      S.push_back(u);
    }
  }
  S.pop_back();
  
  vector<Edge> res;
  vector<int> prevs(N, 1);
  vector<bool> visited(N, false);
  while (!S.empty()) {
    int u = S.back(); S.pop_back();
    //cout << u+1 << "!\n";
    visited[u] = true;
    Edge* e = nullptr;
    int prev = 1;
    for (auto& edge : graph[u]) {
      if (!visited[edge.v]) {
        e = &edge;
      }
      else {
        prev += prevs[edge.v];
      }
    }
    assert (e != nullptr);
    prevs[e->u] = prev;
    e->c = prevs[e->u];
    res.push_back(*e);

    //printf("%d %d %lld\n", e->u+1, e->v+1, e->c);
    int countNonVisitedNeighbor = 0;
    for (const auto& nxtEdge : graph[e->v]) {
      if (!visited[nxtEdge.v]) {
        countNonVisitedNeighbor++;
      }
    }
    if (countNonVisitedNeighbor == 1) {
      S.push_back(e->v);
    }
  }

  assert (res.size() == N-1);
  sort(res.begin(), res.end(), [N, C, H](const auto& lhs, const auto& rhs) -> bool {
      if (H < C) {
        return lhs.c * (N-lhs.c) * lhs.d < rhs.c * (N-rhs.c) * rhs.d;
      }
      else {
        return lhs.c * (N-lhs.c) * lhs.d > rhs.c * (N-rhs.c) * rhs.d;
      }
  });
  //for (int i = 0; i < res.size(); ++i) {
    //printf("%d %d %d %lld %lld\n", res[i].i, res[i].u+1, res[i].v+1, res[i].c, res[i].c * (N-res[i].c) * res[i].d);
  //}
  //printf("\n");
  for (int i = 0; i < K; ++i) {
    printf("%d ", res[res.size()-i-1].i);
  }
  printf("\n");


  return 0;
}
