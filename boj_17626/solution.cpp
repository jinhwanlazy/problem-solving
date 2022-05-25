#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  scanf("%d", &N);
  
  vector<bool> visited(N+1, false);
  queue<pair<int, int>> Q;
  visited[N] = true;
  Q.push({N, 0});
  while (!Q.empty()) {
    auto [n, count] = Q.front(); Q.pop();
    if (n == 0) {
      printf("%d\n", count);
      break;
    }
    for (int i = 1; i * i <= n; ++i)  {
      int nxt = n - i * i;
      assert (nxt >= 0);
      if (!visited[nxt]) {
        visited[nxt] = true;
        Q.push({nxt, count+1});
      }
    }
  }

  return 0;
}
