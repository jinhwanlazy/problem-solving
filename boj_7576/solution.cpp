#include <bits/stdc++.h>
using namespace std;

inline bool boundCheck(int i, int max_i) {
  return 0 <= i && i < max_i;
}

inline bool boundCheck(int i, int min_i, int max_i) {
  return min_i <= i && i < max_i;
}

inline bool boundCheck2d(int i, int j, int max_i, int max_j) {
  return boundCheck(i, max_i) && boundCheck(j, max_j);
}

inline bool boundCheck2d(int i,
                         int j,
                         int min_i,
                         int min_j,
                         int max_i,
                         int max_j) {
  return boundCheck(i, min_i, max_i) && boundCheck(j, min_j, max_j);
}

int main() {
  const static int di[4] = {0, 0, -1, 1};
  const static int dj[4] = {-1, 1, 0, 0};
  int M, N;
  scanf("%d %d", &M, &N);

  vector<vector<int>> grid(N, vector<int>(M));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      scanf("%d", &grid[i][j]);
    }
  }

  vector<vector<bool>> visited(N, vector<bool>(M, false));

  queue<tuple<int, int, int>> Q;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      if (grid[i][j] == 1) {
        Q.push({i, j, 0});
      }
    }
  }

  int ans = 0;
  while (!Q.empty()) {
    int i = get<0>(Q.front());
    int j = get<1>(Q.front());
    int d = get<2>(Q.front());
    Q.pop();
    if (visited[i][j]) {
      continue;
    }
    visited[i][j] = true;
    grid[i][j] = 1;
    ans = max(ans, d);
    for (int k = 0; k < 4; ++k) {
      int ii = i + di[k];
      int jj = j + dj[k];
      if (boundCheck2d(ii, jj, N, M) && grid[ii][jj] == 0) {
        Q.push({ii, jj, d + 1});
      }
    }
  }

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      if (grid[i][j] == 0) {
        printf("-1\n");
        return 0;
      }
    }
  }
  printf("%d\n", ans);

  return 0;
}
