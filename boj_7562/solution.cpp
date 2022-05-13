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
  int i, j, depth;
};

int solution() {
  static int di[8]{-2, -2, -1, -1, +1, +1, +2, +2};
  static int dj[8]{-1, +1, -2, +2, -2, +2, -1, +1};
  int L;
  scanf("%d", &L);

  int i, j;
  scanf("%d %d", &i, &j);

  int i_dst, j_dst;
  scanf("%d %d", &i_dst, &j_dst);

  vector<vector<int>> grid(L, vector<int>(L, -1));

  queue<State> Q;
  Q.push({i, j, 0});
  while (!Q.empty()) {
    State s = Q.front();
    Q.pop();
    if (grid[s.i][s.j] != -1) {
      continue;
    }
    if (s.i == i_dst && s.j == j_dst) {
      printf("%d\n", s.depth);
      return 0;
    }
    grid[s.i][s.j] = s.depth;
    for (int k = 0; k < 8; ++k) {
      int ii = s.i + di[k];
      int jj = s.j + dj[k];
      if (boundCheck2d(ii, jj, L, L) && grid[ii][jj] == -1) {
        Q.push({ii, jj, s.depth + 1});
      }
    }
  }
  throw;
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    solution();
  }
  int L;
  scanf("%d", &L);

  return 0;
}
