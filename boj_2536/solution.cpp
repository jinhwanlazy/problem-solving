#include <bits/stdc++.h>
using namespace std;

void solve() {
  int N, M;
  scanf("%d %d", &N, &M);

  int K;
  scanf("%d", &K);

  map<pair<int, int>, vector<pair<int, int>>> lines;
  for (int i = 0; i < K; ++i) {
    int b, x1, y1, x2, y2;
    scanf("%d %d %d %d %d", &b, &x1, &y1, &x2, &y2);
    
    lines[{x1, y1}].push_back({x2, y2});
    lines[{x2, y2}].push_back({x1, y1});
  }

  int xs, ys, xd, yd;
  scanf("%d %d %d %d", &xs, &ys, &xd, &yd);
  
  struct State {
    int count;
    int x, y;
  };
  
  set<pair<int, int>> visited;
  queue<State> Q;
  Q.push({0, xs, ys});
  while (!Q.empty()) {
    auto [c, x, y] = Q.front(); Q.pop();
    if (x == xd && y == yd) {
      printf("%d\n", c);
      return;
    }
    cout << c << ", " << x << ", " << y << "\n";
    visited.insert({x, y});
    for (auto nxt : lines[{x, y}]) {
      if (visited.find(nxt) == visited.end()) {
        Q.push({c+1, nxt.first, nxt.second});
      }
    }
  }
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
