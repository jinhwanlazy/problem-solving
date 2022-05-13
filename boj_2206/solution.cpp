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

struct State {
  int i;
  int j;
  bool hammer_used;
  int distance;
};

int main() {
  static int di[4] = {0, 0, -1, 1};
  static int dj[4] = {-1, 1, 0, 0};

  int N, M;
  scanf("%d %d", &N, &M);

  vector<string> grid(N);
  for (int i = 0; i < N; ++i) {
    cin >> grid[i];
  }

  int ans = numeric_limits<int>::max();
  vector<vector<vector<bool>>> visited(
      2, vector<vector<bool>>(N, vector<bool>(M, false)));
  queue<State> Q;
  Q.push(State{0, 0, false, 1});
  while (!Q.empty()) {
    State s = Q.front();
    Q.pop();
    if (visited[s.hammer_used][s.i][s.j]) {
      continue;
    }
    visited[s.hammer_used][s.i][s.j] = true;
    if (s.i == N - 1 && s.j == M - 1) {
      ans = min(ans, s.distance);
    }
    for (int k = 0; k < 4; ++k) {
      int ii = s.i + di[k];
      int jj = s.j + dj[k];
      if (boundCheck2d(ii, jj, N, M)) {
        if (grid[ii][jj] == '0' && !visited[s.hammer_used][ii][jj]) {
          Q.push({ii, jj, s.hammer_used, s.distance + 1});
        }
        if (grid[ii][jj] == '1' && !s.hammer_used && !visited[1][ii][jj]) {
          Q.push({ii, jj, true, s.distance + 1});
        }
      }
    }
  }
  if (ans == numeric_limits<int>::max()) {
    printf("-1\n");
  } else {
    printf("%d\n", ans);
  }

  return 0;
}
