#include <bits/stdc++.h>
using namespace std;

void solve() {
  int N, K;
  scanf("%d %d", &N, &K);

  vector<int> visitCount(100001, 0);
  vector<int> depth(100001, -1);
  visitCount[N] = 0;
  depth[N] = 0;
  queue<pair<int, int>> Q;
  Q.push({N, 0});
  while (!Q.empty()) {
    auto [u, d] = Q.front(); 
    Q.pop();

    if (depth[u] == -1) {
      depth[u] = d;
      visitCount[u]++;
    } else if (depth[u] == d) {
      visitCount[u]++;
    } 
    else {
      continue;
    }

    if (depth[K] != -1 && depth[K] <= d) {
      continue;
    }
    
    if (u > 0) {
      Q.push({u-1, d+1});
    }
    if (u < 100000) {
      Q.push({u+1, d+1});
    }
    if (u * 2 <= 100000) {
      Q.push({u*2, d+1});
    }
  }

  printf("%d\n", depth[K]);
  printf("%d\n", visitCount[K]);
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
