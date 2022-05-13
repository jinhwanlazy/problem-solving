#include <bits/stdc++.h>
using namespace std;

constexpr static int di[4] = {0, 0, -1, +1};
constexpr static int dj[4] = {-1, +1, 0, 0};

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
  int i, j;
  int mask = 0;
};

int set_visited(int mask, char c) {
  return mask | (1 << (c - 'A'));
}

bool is_visited(int mask, char c) {
  return (mask >> (c - 'A')) & 1;
}

int bit(char i) {
  return (int)1 << (i - 'A');
}

int main() {
  int R, C;
  scanf("%d %d", &R, &C);

  vector<string> board(R);
  for (int i = 0; i < R; ++i) {
    cin >> board[i];
  }

  vector<State> S;
  S.push_back({0, 0, bit(board[0][0])});
  int ans = 0;
  while (!S.empty()) {
    auto [i, j, v] = S.back();
    S.pop_back();
    ans = max(ans, __builtin_popcount(v));
    for (int k = 0; k < 4; ++k) {
      int ii = i + di[k];
      int jj = j + dj[k];
      if (boundCheck2d(ii, jj, R, C) && !is_visited(v, board[ii][jj])) {
        S.push_back({ii, jj, set_visited(v, board[ii][jj])});
      }
    }
  }
  cout << ans << "\n";
  return 0;
}
