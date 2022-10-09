#include <bits/stdc++.h>
using namespace std;

void solve() {
  int F, S, G;
  scanf("%d %d %d", &F, &S, &G);
  int U, D;
  scanf("%d %d", &U, &D);

  vector<bool>  visited(F+1);
  queue<pair<int, int>> Q;
  Q.push({0, S});
  while (!Q.empty()) {
    auto [c, i] = Q.front(); Q.pop();
    if (visited[i]) {
      continue;
    }
    visited[i] = true;
    if (i == G) {
      printf("%d\n", c);
      return;
    }
    int u = i + U;
    if (u <= F && !visited[u]) {
      Q.push({c+1, u});
    }
    int d = i - D;
    if (d >= 1 && !visited[d]) {
      Q.push({c+1, d});
    }
  }
  printf("use the stairs\n");
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
