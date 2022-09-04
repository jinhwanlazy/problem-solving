#include <bits/stdc++.h>
#include <cstdio>
using namespace std;

constexpr static int di[4] = {0, 1, 0, -1};
constexpr static int dj[4] = {1, 0, -1, 0};

void solve() {
  int H, W;
  scanf("%d %d", &H, &W);

  set<char> keys;
  map<char, pair<int, int>> doors;
  queue<pair<int, int>> Q, holdBacks;
  set<pair<int, int>> visited;

  vector<vector<char>> grid(H, vector<char>(W));
  for (int i = 0; i < H; ++i) {
    for (int j = 0; j < W; ++j) {
      char& c = grid[i][j];
      scanf(" %c", &c);

      if (c < 'a') {
        doors[c] = {i, j};
      }
      if (c != '*' && (i == 0 || i == H-1 || j == 0 || j == W-1)) {
        Q.push({i, j});
      }
    }
  }

  string inventory;
  cin >> inventory;
  if (inventory != "0") {
    for (char c : inventory) {
      keys.insert(toupper(c));
    }
  }

  int ans = 0;
  while (!Q.empty()) {
    auto [i, j] = Q.front();
    
    Q.pop();
    if (visited.find({i, j}) != visited.end()) {
      continue;
    }
    char& c = grid[i][j];
    if ('A' <= c && c <= 'Z') {
      if (keys.find(c) == keys.end()) {
        holdBacks.push({i, j});
        continue;
      }
      else {
        c = '.';
      }
    } else if ('a' <= c && c <= 'z') {
      keys.insert(toupper(c));
      c = '.';
      while (!holdBacks.empty()) {
        Q.push(holdBacks.front());
        holdBacks.pop();
      }
    } else if (c == '$') {
      c = '.';
      ans += 1;
    }
    visited.insert({i, j});

    for (int k = 0; k < 4; ++k) {
      int ii = i + di[k];
      int jj = j + dj[k];
      if (!(0 <= ii && ii < H && 0 <= jj && jj < W)) {
        continue;
      }
      char& c = grid[ii][jj];
      if (c == '*' || visited.find({ii, jj}) != visited.end()) {
        continue;
      }  
      Q.push({ii, jj});
    }
  }

  //for (int i = 0; i < grid.size(); ++i) {
    //for(int j = 0; j < grid[i].size(); ++j) {
      //printf("%c", grid[i][j]);
    //}
    //printf("\n");
  //}
  
  printf("%d\n", ans);
}

int main() {
  int T;
  scanf("%d", &T);
  
  while (T--) {
    solve();
  }

  return 0;
}
