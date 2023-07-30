#include <bits/stdc++.h>
using namespace std;

void solve() {
  int N;
  scanf("%d", &N);

  vector<int> xs(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &xs[i]);
  }

  vector<vector<int>> data;
  map<int, int> tree;
  for (int x : xs) {
    if (data.empty()) {
      tree[-x] = data.size();
      data.push_back({x});
    }
    else {
      auto it = tree.upper_bound(-x);
      if (it == tree.end()) {
        tree[-x] = data.size();
        data.push_back({x});
      }
      else {
        auto& row = data[it->second];
        row.push_back(x);
        tree[-x] = it->second;
        tree.erase(it);
      }
    }
  }
  for (const auto& row : data) {
    for (int i = 0; i < row.size(); ++i) {
      printf("%d ", row[i]);
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
