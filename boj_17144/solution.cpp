#include <bits/stdc++.h>
using namespace std;

constexpr static int di[4] = {0, 1, 0, -1};
constexpr static int dj[4] = {1, 0, -1, 0};

void genLoops(const vector<vector<int>>& room,
              vector<pair<int, int>>& loop1,
              vector<pair<int, int>>& loop2) {
  int R = room.size();
  int C = room[0].size();
  for (int i = 1; i < R-1; ++i) {
    if (room[i][0] != -1) 
      continue;
    if (loop1.empty()) {
      for (int r = i - 1; r >= 0; --r) 
        loop1.push_back({r, 0});
      for (int c = 1; c < C; ++c) 
        loop1.push_back({0, c});
      for (int r = 1; r <= i; ++r) 
        loop1.push_back({r, C-1});
      for (int c = C-2; c > 0; --c) 
        loop1.push_back({i, c});
    } else {
      for (int r = i + 1; r < R; ++r) 
        loop2.push_back({r, 0});
      for (int c = 1; c < C; ++c) 
        loop2.push_back({R-1, c});
      for (int r = R-2; r >= i; --r) 
        loop2.push_back({r, C-1});
      for (int c = C-2; c > 0; --c) 
        loop2.push_back({i, c});
    }
  }
}

void diffuse(vector<vector<int>>& room) {
  int R = room.size();
  int C = room[0].size();
  vector<vector<int>> diff(R, vector<int>(C, 0));
  
  for (int i = 0; i < R; ++i) {
    for (int j = 0; j < C; ++j) {
      int cnt = 0;
      for (int k = 0; k < 4; ++k) {
        int ii = i + di[k];
        int jj = j + dj[k];
        if (!(0 <= ii && ii < R && 0 <= jj && jj < C)) {
          continue;
        }
        if (room[ii][jj] == -1) {
          continue;
        }
        cnt++;
        diff[ii][jj] += room[i][j] / 5;
      }
      diff[i][j] -= room[i][j] / 5 * cnt;
    }
  }
  for (int i = 0; i < R; ++i) {
    for (int j = 0; j < C; ++j) {
      if (room[i][j] != -1) {
        room[i][j] += diff[i][j];
      }
    }
  }
}

void circulate(vector<vector<int>>& room,
               vector<pair<int, int>>& loop) {
  auto [i, j] = loop.front();
  int res = room[i][j];
  room[i][j] = 0;
  for (size_t i = 0; i < loop.size()-1; ++i) {
    auto [i1, j1] = loop[i];
    auto [i2, j2] = loop[i+1];
    swap(room[i1][j1], room[i2][j2]);
  }
}

void solve() {
  int R, C, T;
  scanf("%d %d %d", &R, &C, &T);

  vector<vector<int>> room(R, vector<int>(C));
  for (int i = 0; i < R; ++i) {
    for (int j = 0; j < C; ++j) {
      scanf("%d", &room[i][j]);
    }
  }

  vector<pair<int, int>> loop1, loop2;
  genLoops(room, loop1, loop2);

  while (T--) {
    diffuse(room);
    circulate(room, loop1);
    circulate(room, loop2);
  }

  int ans = 0;
  for (int i = 0; i < R; ++i) {
    for (int j = 0; j < C; ++j) {
      if (room[i][j] != -1) {
        ans += room[i][j];
      }
    }
  }
  printf("%d\n", ans);
  
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
