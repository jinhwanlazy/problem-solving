#include <bits/stdc++.h>
using namespace std;

constexpr static int INF = numeric_limits<int>::max();

void solve() {
  int N, M;
  scanf("%d %d", &N, &M);

  vector<pair<int, int>> homes;
  vector<pair<int, int>> chicks;
  homes.reserve(N * N);
  chicks.reserve(N * N);

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      int x;
      scanf("%d", &x);
      if (x == 0) {
        continue;
      } else if (x == 1) {
        homes.emplace_back(i, j);
      } else {
        chicks.emplace_back(i, j);
      }
    }
  }

  vector<vector<int>> dist(homes.size(), vector<int>(chicks.size(), INF));
  for (int i = 0; i < homes.size(); ++i) {
    for (int j = 0; j < chicks.size(); ++j) {
      dist[i][j] = abs(homes[i].first - chicks[j].first) + abs(homes[i].second - chicks[j].second);
    }
  }
  
  stack<vector<int>> st;
  for (int i = chicks.size()-1; i >= 0; --i) {
    st.push({i});
  }
  int ans = INF;
  while (!st.empty()) {
    vector<int> selected = st.top(); st.pop();
    if (selected.size() == M) {
      int res = 0;
      for (int i = 0; i < homes.size(); ++i) {
        int d = INF;
        for (int j : selected) {
          d = min(d, dist[i][j]);
        }
        res += d;
      }
      ans = min(ans, res);
    }

    for (int i = chicks.size()-1; i > selected.back(); --i) {
      selected.push_back(i);
      st.push(selected);
      selected.pop_back();
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
