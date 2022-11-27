#include <bits/stdc++.h>
using namespace std;

constexpr static int di[4] = {0, 1, 0, -1};
constexpr static int dj[4] = {1, 0, -1, 0};

int count(const vector<vector<bool>>& W) {
  int res = 0;
  for (const auto& row : W) {
    for (const auto& c : row) {
      res += c;
    }
  }
  return res;
}

void step(vector<vector<bool>>& W) {
  queue<pair<int, int>> Q;
  set<pair<int, int>> visited;
  set<pair<int, int>> toDelete;
  Q.push({0, 0});
  while (!Q.empty()) {
    auto [i, j] = Q.front();
    Q.pop();
    if (visited.find({i, j}) != visited.end()) {
      continue;
    }
    visited.insert({i, j});
    for (int k = 0; k < 4; ++k) {
      int ii = i + di[k];
      int jj = j + dj[k];
      if (0 <= ii && ii < W.size() && 0 <= jj && jj < W[0].size()) {
        if (W[ii][jj]) {
          toDelete.insert({ii, jj});
        }
        else if (visited.find({ii, jj}) == visited.end()) {
          Q.push({ii, jj});
        }
      }
    }
  }
  for (auto [i, j] : toDelete) {
    W[i][j] = 0;
  }
}

void solve() {
  int N, M;
  scanf("%d %d", &N, &M);
  vector<vector<bool>> W(N+2, vector<bool>(M+2));
  for (int i = 1; i <= N; ++i) {
    for (int j = 1; j <= M; ++j) {
      int c;
      scanf("%d", &c);
      W[i][j] = (c == 1);
    }
  }
  int stepCount = 0;
  int remaining = count(W);
  while (true) {
    stepCount++;
    step(W);
    int next = count(W);
    if (next == 0) {
      printf("%d\n%d\n", stepCount, remaining);
      break;
    }
    remaining = next;
  }
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
