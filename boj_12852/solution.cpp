#include <bits/stdc++.h>
using namespace std;

constexpr static int INF = numeric_limits<int>::max();

int main() {
  int N;
  scanf("%d", &N);

  vector<int> trace(N + 1, -1);
  vector<int> cost(N + 1, INF);

  cost[1] = 0;
  trace[1] = 0;

  for (int i = 2; i <= N; ++i) {
    if (cost[i - 1] + 1 < cost[i]) {
      cost[i] = cost[i - 1] + 1;
      trace[i] = i - 1;
    }
    if (i % 2 == 0 && cost[i / 2] + 1 < cost[i]) {
      cost[i] = cost[i / 2] + 1;
      trace[i] = i / 2;
    }
    if (i % 3 == 0 && cost[i / 3] + 1 < cost[i]) {
      cost[i] = cost[i / 3] + 1;
      trace[i] = i / 3;
    }
  }

  int d = N;
  printf("%d\n", cost[d]);
  while (d > 0) {
    printf("%d ", d);
    d = trace[d];
  }
  printf("\n");

  return 0;
}
