#include <bits/stdc++.h>
using namespace std;

void solve() {
  int N;
  cin >> N;

  vector<vector<int>> graph(N);

  int M;
  cin >> M;
  for (int i = 0; i < M; ++i) {
    int u, v;
    cin >> u >> v;
    --u; --v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  set<int> step1, step2;
  for (int j : graph[0]) {
    step1.insert(j);
  }
  
  for (int i : step1) {
    for (int j : graph[i]) {
      step2.insert(j);
    }
  }
  step1.insert(step2.begin(), step2.end());
  step1.erase(0);
  cout << step1.size() << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL); cout.tie(NULL);

  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
