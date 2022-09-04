#include <bits/stdc++.h>
using namespace std;

constexpr static int di[4] = {0, 1, 0, -1};
constexpr static int dj[4] = {1, 0, -1, 0};

void solve() {
  int N, M;
  scanf("%d %d", &N, &M);

  vector<vector<int>> grid(N, vector<int>(M));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      char c;
      scanf(" %c", &c);
      grid[i][j] = c - '0';
    }
  }

  // id -> area
  map<int, int> area; 

  int id = 2;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      if (grid[i][j] != 0) {
        continue;
      }
      int count = 1;
      grid[i][j] = id;
      queue<pair<int, int>> Q;
      Q.push({i, j});
      while (!Q.empty()) {
        auto [i, j] = Q.front(); Q.pop();
        for (int k = 0; k < 4; ++k) {
          int ii = i + di[k];
          int jj = j + dj[k];
          if (0 <= ii && ii < N && 0 <= jj && jj < M && grid[ii][jj] == 0) {
            grid[ii][jj] = id;
            count++;
            Q.push({ii, jj});
          }
        }
      }
      area[id] = count;
      id++;
    }
  }

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      if (grid[i][j] > 1) {
        printf("0");
        continue;
      } 
      set<int> ids;
      for (int k = 0; k < 4; ++k) {
        int ii = i + di[k];
        int jj = j + dj[k];
        if (0 <= ii && ii < N && 0 <= jj && jj < M && grid[ii][jj] > 1) {
          ids.insert(grid[ii][jj]);
        }
      }
      int ans = 1;
      for (int id : ids) {
        ans += area[id];
      }
      printf("%d", ans % 10);
    }
    printf("\n");
  }
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
