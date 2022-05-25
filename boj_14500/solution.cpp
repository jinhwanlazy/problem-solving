#include <bits/stdc++.h>
using namespace std;

using Coord = pair<int, int>;
using Tetromino = vector<Coord>;

static vector<Tetromino> base_tetrominos = {
  {{0, 0}, {0, 1}, {0, 2}, {0, 3}},
  {{0, 0}, {0, 1}, {1, 0}, {1, 1}},
  {{0, 0}, {1, 0}, {2, 0}, {2, 1}},
  {{0, 0}, {1, 0}, {1, 1}, {2, 1}},
  {{0, 0}, {0, 1}, {0, 2}, {1, 1}},
};

Coord mirror_x(const Coord& coord) {
  return {-coord.first, coord.second};
}

Coord rot90(const Coord& coord) {
  return {-coord.second, coord.first};
}

Tetromino augment(
    const Tetromino& tetromino,
    const function<Coord(const Coord&)>& transform) {
  return {transform(tetromino[0]), transform(tetromino[1]),
          transform(tetromino[2]), transform(tetromino[3])};
}

vector<Tetromino> augment(const vector<Tetromino>& tetrominos) {
  vector<Tetromino> res;
  for (const auto& t : tetrominos) {
    res.push_back(t);
    res.push_back(augment(t, [](const Coord& c) { return rot90(c); }));
    res.push_back(augment(t, [](const Coord& c) { return rot90(rot90(c)); }));
    res.push_back(augment(t, [](const Coord& c) { return rot90(rot90(rot90(c))); }));
    res.push_back(augment(t, [](const Coord& c) { return mirror_x(c); }));
    res.push_back(augment(t, [](const Coord& c) { return rot90(mirror_x(c)); }));
    res.push_back(augment(t, [](const Coord& c) { return rot90(rot90(mirror_x(c))); }));
    res.push_back(augment(t, [](const Coord& c) { return rot90(rot90(rot90(mirror_x(c)))); }));
  }
  return res;
}

int main() {
  int N, M;
  scanf("%d %d", &N, &M);
  
  vector<vector<int>> grid(N, vector<int>(M));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      scanf("%d", &grid[i][j]);
    }
  }

  auto tetrominos = augment(base_tetrominos);

  int ans = 0;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      for (const auto& t : tetrominos) {
        int score = 0;
        bool out_of_bound = false;
        for (int k = 0; k < 4; ++k) {
          int ii = i + t[k].first;
          int jj = j + t[k].second;
          if (ii < 0 || N <= ii || jj < 0 || M <= jj) {
            out_of_bound = true;
            break;
          }
          score += grid[ii][jj];
        }
        if (!out_of_bound) {
          ans = max(ans, score);
        }
      }
    }
  }
  printf("%d\n", ans);

  return 0;
}
