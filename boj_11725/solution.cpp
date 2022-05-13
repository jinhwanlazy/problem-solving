#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  scanf("%d", &N);

  vector<vector<int>> tree(N + 1, vector<int>());
  for (int i = 0; i < N; ++i) {
    int A, B;
    scanf("%d %d", &A, &B);
    tree[A].push_back(B);
    tree[B].push_back(A);
  }

  vector<int> parent(N + 1, -1);
  queue<int> Q;
  Q.push(1);
  while (!Q.empty()) {
    int u = Q.front();
    Q.pop();
    for (int v : tree[u]) {
      if (parent[v] == -1) {
        parent[v] = u;
        Q.push(v);
      }
    }
  }
  for (int i = 2; i <= N; ++i) {
    printf("%d\n", parent[i]);
  }

  return 0;
}
