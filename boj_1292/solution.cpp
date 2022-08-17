#include <bits/stdc++.h>
using namespace std;

void solve() {
  vector<int> table;
  table.reserve(1001);
  table.push_back(0);
  for (int i = 1; table.size() < 1001; ++i) {
    for (int j = 0; j < i; ++j) {
      table.push_back(i);
    }
  }

  int N, M;
  scanf("%d %d", &N, &M);

  int res = 0;
  for (int i = N; i <= M; ++i) {
    res += table[i];
  }
  printf("%d\n", res);
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
