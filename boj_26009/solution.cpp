#include <bits/stdc++.h>
using namespace std;

constexpr static int di[4] = {0, 1, 0, -1};
constexpr static int dj[4] = {1, 0, -1, 0};

void solve() {
  int N, M;
  scanf("%d %d", &N, &M);

  vector<vector<bool>> blocked(N, vector<bool>(M, false));
  int K;
  scanf("%d", &K);
  while (K--) {
    int r, c, d;
    scanf("%d %d %d", &r, &c, &d);
    r--;
    c--;

    for (int di = -d; di <= d; ++di) {
      int dj = d - abs(di);
      int ii = r + di;
      if (ii < 0 || N <= ii) {
        continue;
      }
      if (c - dj >= 0) 
        blocked[ii][c-dj] = true;
      if (c + dj < M) 
        blocked[ii][c+dj] = true;
    }
  }

  struct State {
    int i, j, step;
  };

  vector<vector<bool>> visited(N, vector<bool>(M, false));
  queue<State> Q;
  Q.push({0, 0, 0});
  while (!Q.empty()) {
    auto [i, j, step] = Q.front(); Q.pop();
    if (visited[i][j]) 
      continue;
    visited[i][j] = true;
    if (i == N-1 && j == M-1) {
      printf("YES\n%d\n", step);
      return;
    }

    for (int k = 0; k < 4; ++k) {
      int ii = i + di[k];
      int jj = j + dj[k];
      if (ii < 0 || N <= ii) 
        continue;
      if (jj < 0 || M <= jj) 
        continue;
      if (blocked[ii][jj] || visited[ii][jj])  
        continue;
      Q.push({ii, jj, step+1});
    }
  }
  printf("NO\n");
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
