#include <bits/stdc++.h>
#include <ratio>
using namespace std;

static constexpr int UP = 1;
static constexpr int DOWN = -1;

void solve() {
  int N;
  scanf("%d", &N);
  
  map<int, vector<int>> coords;
  for (int i = 0; i < N; ++i) {
    int x, y;
    scanf("%d %d", &x, &y);
    coords[x].push_back(y);
  }

  int M;
  scanf("%d", &M);
  vector<int> K(M);
  for (int i = 0; i < M; ++i) {
    scanf("%d", &K[i]);
  }

  for (auto& [x, ys] : coords) {
    sort(ys.begin(), ys.end());
  }
  vector<int> directions(coords.size());
  directions[0] = coords[0].front() == 0 ? UP : DOWN;
  if (directions[0] == DOWN) {
    reverse(coords[0].begin(), coords[0].end());
  }
  vector<pair<int, int>> ans(1);
  for (auto y : coords[0]) {
    ans.push_back({0, y});
  }

  int i = 1;
  auto prev = coords.begin();
  auto it = next(prev);
  while (it != coords.end()) {
    directions[i] = prev->second.back() == it->second.front() ? UP : DOWN;
    if (directions[i] == DOWN) {
      reverse(it->second.begin(), it->second.end());
    }
    for (auto y : it->second) {
      ans.push_back({it->first, y});
      //printf("%d %d\n", it->first, y);
    }
    prev = it;
    it = next(prev);
    i++;
  }
  for (auto k : K) {
    printf("%d %d\n", ans[k].first, ans[k].second);
  }
  
}

int main() {
  int T;
  scanf("%d", &T);
  
  while (T--) {
    solve();
  }

  return 0;
}
